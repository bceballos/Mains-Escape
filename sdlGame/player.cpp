#include <iostream>

#include <SDL_mixer.h>
#include "SDL.h"
#include "hPlayer.h"
#include "hGameEngine.h"
#include "SDL_image.h"
#include "hKeys.h"
#include "hTimer.h"

#include <cmath>

void Player::init(Type t, /*int r, int g, int b,*/ int x, int y, int blockSize, int health, SDL_Renderer* renderer, Logging* log) {
	rect.x = x;
	rect.y = y;
	rect.w = blockSize;
	rect.h = blockSize;
	temp.x = x;
	temp.y = y;
	temp.w = blockSize;
	temp.h = blockSize;
	textureRect.x = 0;
	textureRect.y = 0;
	textureRect.w = blockSize;
	textureRect.h = blockSize;
	this->t = t;
	//this->r = r;
	//this->g = g;
	//this->b = b;
	this->health = health;
	this->chosenHealth = health;
	this->blockSize = blockSize;
	particleEffect = new ParticleManager();
	initRenderTexture(renderer);
}

void Player::input(SDL_Event movement, Logging* log, Keys keys, SDL_Joystick* gamePad) {
	SDL_Keycode keyPressed = movement.key.keysym.sym;
	if (movement.type == SDL_KEYUP)
	{
		if (movement.key.keysym.sym == keys.sprint) {
			log->logInput("KEYUP", movement.key.timestamp, keyPressed);
			speed = 1.0f;
		}
		keyboardPresses.clear();
	}
	else {
		if (movement.type == SDL_JOYAXISMOTION) {
			if (ceil((SDL_JoystickGetAxis(gamePad, 2))) > -30000) {
				speed = 2.0f;
			}
			if (ceil((SDL_JoystickGetAxis(gamePad, 2))) < 0) {
				speed = 1.0f;
			}
			if (ceil((SDL_JoystickGetAxis(gamePad, 1)) / 3276.70f) <= -8) {
				keyboardPresses.push_back(FORWARD);
			}
			if (ceil((SDL_JoystickGetAxis(gamePad, 0)) / 3276.70f) <= -8) {
				keyboardPresses.push_back(LEFT);
			}
			if (ceil((SDL_JoystickGetAxis(gamePad, 0)) / 3276.70f) >= 8) {
				keyboardPresses.push_back(RIGHT);
			}
			if (ceil((SDL_JoystickGetAxis(gamePad, 1)) / 3276.70f) >= 8) {
				keyboardPresses.push_back(BACKWARDS);
			}
			if (ceil((SDL_JoystickGetAxis(gamePad, 1)) / 3276.70f) >= -9 && ceil((SDL_JoystickGetAxis(gamePad, 1)) / 3276.70f) <= 9 && ceil((SDL_JoystickGetAxis(gamePad, 0)) / 3276.70f) >= -9 && ceil((SDL_JoystickGetAxis(gamePad, 0)) / 3276.70f) <= 9) {
				keyboardPresses.clear();
			}
		}
		else {

		}
		if (movement.key.keysym.sym == keys.sprint) {
			speed = 2.0f;
		}
		if (movement.key.keysym.sym == keys.forward) {
			log->logInput("KEYDOWN", movement.key.timestamp, keyPressed);
			keyboardPresses.push_back(FORWARD);
		}
		if (movement.key.keysym.sym == keys.left ) {
			log->logInput("KEYDOWN", movement.key.timestamp, keyPressed);
			keyboardPresses.push_back(LEFT);
		}
		if (movement.key.keysym.sym == keys.right) {
			log->logInput("KEYDOWN", movement.key.timestamp, keyPressed);
			keyboardPresses.push_back(RIGHT);
		}
		if (movement.key.keysym.sym == keys.backward) {
			log->logInput("KEYDOWN", movement.key.timestamp, keyPressed);
			keyboardPresses.push_back(BACKWARDS);
		}
	}

}

void Player::shiftDirection(Logging* log) {
	if (!keyboardPresses.empty()) {
		switch (keyboardPresses[0]) {
		case FORWARD:
			lastMovement = 2;
			temp.y -= 20;
			break;
		case BACKWARDS:
			lastMovement = 0;
			temp.y += 20;
			break;
		case RIGHT:
			lastMovement = 3;
			temp.x += 20;
			break;
		case LEFT:
			lastMovement = 1;
			temp.x -= 20;
			break;
		}
		playerMove = MOVING;
		log->logPositioning(temp, "player temp rect");
	}
	else {
		playerMove = NONE;
	}
}


void Player::lateUpdate(std::vector<GameObject*> tiles, std::vector<Door*> doors, std::vector<Enemy*> &enemy, SDL_Renderer* renderer, Logging* log, float endTime)
{
	temp.x = std::fmax(0, std::fmin(temp.x, Game::windowWidth));
	temp.y = std::fmax(0, std::fmin(temp.y, Game::windowHeight - 60));

	int x = (temp.x / 20);
	int y = (temp.y / 20);

	GameObject* collisionTile = tiles[x + (y * Game::windowRows)];

	switch (collisionTile->t)
	{
	case GameObject::Type::EMPTY:
		doorDamaged = false;
		rect.x = temp.x;
		rect.y = temp.y;
		log->logPositioning(temp, "player rect");
		if (collisionTile->passedEmpty == true) {
			score += 10;
			collisionTile->passedEmpty = false;
			log->logGeneral("score increased, tile passed = true");
		}

		break;

	case GameObject::Type::WALL:
		break;

	case GameObject::Type::FINISH:
		if (collisionTile->rect.x == temp.x && collisionTile->rect.y == temp.y && endTime <= 1) {
			if (collisionTile->passedEmpty == true) {
				rect.x = temp.x;
				rect.y = temp.y;
				score += 1000;
				collisionTile->passedEmpty = false;
			}
		}
		break;

	case GameObject::Type::DOOR:
		for (Door* object : doors) {
			if ((collisionTile->rect.x == object->rect.x) && (collisionTile->rect.y == object->rect.y)) {
				if (object->active != true) {
					doorDamaged = false;
					rect.x = temp.x;
					rect.y = temp.y;
				}
				else if (object->rect.x == rect.x && object->rect.y == rect.y) {
					if (object->active == true) {
						if (!sfxToggle) {
							Mix_PlayChannel(-1, hurtSFX, 0);
							Mix_PlayChannel(-1, particleSFX, 0);
						}
						if (!doorDamaged) {
							health--;
							particleEffect->init(renderer, 45, rect.x, rect.y);
							doorDamaged = true;
						}
					}
				}
				else {
					log->logCollision("Player collided with a closed door at position x: " + std::to_string(temp.x) + " y: " + std::to_string(temp.y));
				}
			}
		}
		break;
	}

	for (int i = 0; i < enemy.size();) {
		if ((collisionTile->rect.x == enemy[i]->rect.x) && (collisionTile->rect.y == enemy[i]->rect.y)) {
			health--;
			particleEffect->init(renderer, 45, rect.x, rect.y);
			if (!sfxToggle) {
				Mix_PlayChannel(-1, hurtSFX, 0);
				Mix_PlayChannel(-1, particleSFX, 0);
			}
			delete enemy[i];
			enemy.erase(enemy.begin() + i);

			log->logCollision("Player collided with an at position x: " + std::to_string(rect.x) + " y: " + std::to_string(rect.y));
			if (health == 0 ) {
				score -= 100;
				init(GameObject::Type::PLAYER, 380, 0, blockSize, chosenHealth, renderer, log);
				
			}
		}
		else {
			i++;
		}
	}

	temp = SDL_Rect{rect.x, rect.y, rect.w, rect.h};
	log->logCollision("Player collided, temp rect reset to the previous position");
}

void Player::update(Logging* log) {
	float now = SDL_GetTicks();

	if ((now - lastMovementTime) >= (75 / speed))
	{
		lastMovementTime = now;
		shiftDirection(log);
		setRenderTexture();
	}

	particleEffect->update();
}

void Player::initRenderTexture(SDL_Renderer* renderer) {
	IMG_Init(SDL_INIT_EVERYTHING);
	surface = IMG_Load("Assets/Sprites/playerSheet.png");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void Player::setRenderTexture() {
	if (playerMove == NONE) {
		textureRect.x = lastMovement * 20;
		textureRect.y = 0;
	}
	else {
		looper += 20;
		if (looper > 60) {
			looper = 0;
		}
		textureRect.x = lastMovement * 20;
		textureRect.y = looper;
	}
}

void Player::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, &textureRect, &rect);
	particleEffect->render(renderer);
}