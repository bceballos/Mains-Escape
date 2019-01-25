#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "hEnemy.h"
#include "hGameEngine.h"

#include <cmath>

void Enemy::init(Type t,/* int r, int g, int b,*/ int x, int y, int blockSize, SDL_Renderer* renderer, Logging* log) {
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
	initRenderTexture(renderer, log);
	log->logGeneral("enemy initialized at position " + std::to_string(rect.x) + ", " + std::to_string(rect.y));
}

void Enemy::shiftDirection(Logging* log) {
	switch (enemyMove) {
	case FORWARD:
		temp.y -= 20;
		break;
	case BACKWARDS:
		temp.y += 20;
		break;
	case RIGHT:
		temp.x += 20;
		break;
	case LEFT:
		temp.x -= 20;
		break;
	}
	log->logPositioning(temp, "enemy temp rect");
}

void Enemy::randomMove() {
	int direction = rand() % 4 + 1;
	switch (direction)
	{
	case 1:
		enemyMove = FORWARD;
		lastMovement = 0;
		break;
	case 2:
		enemyMove = BACKWARDS;
		lastMovement = 0;
		break;
	case 3:
		enemyMove = LEFT;
		lastMovement = 2;
		break;
	case 4:
		enemyMove = RIGHT;
		lastMovement = 1;
		break;
	}
}

// Black magic, do not change the collision
void Enemy::lateUpdate(std::vector<GameObject*> tiles, std::vector<Door*> doors, Logging* log)
{
	temp.x = std::fmax(0, std::fmin(temp.x, Game::windowWidth));
	temp.y = std::fmax(0, std::fmin(temp.y, Game::windowHeight - 60));

	int x = (temp.x / 20);
	int y = (temp.y / 20);

	GameObject* collisionTile = tiles[x + (y * Game::windowRows)];

	switch (collisionTile->t)
	{
	case GameObject::Type::EMPTY:

		rect.x = temp.x;
		rect.y = temp.y;
		log->logPositioning(rect, "enemy rect");
		break;

	case GameObject::Type::WALL:
		randomMove();
		break;

	case GameObject::Type::DOOR:
		for (Door* object : doors) {
			if ((collisionTile->rect.x == object->rect.x) && (collisionTile->rect.y == object->rect.y)) {
				if (object->active != true) {
					rect.x = temp.x;
					rect.y = temp.y;
					log->logCollision("Enemy collided with a closed door at position x: " + std::to_string(temp.x) + " y: " + std::to_string(temp.y));
				}
				else {
					randomMove();
				}
			}
		}
		break;
	} 

	temp = SDL_Rect{ rect.x, rect.y, rect.w, rect.h };
}

void Enemy::update(Logging* log) {
	float now = SDL_GetTicks();
	if ((now - lastMovementTime) >= (150))
	{
		lastMovementTime = now;
		shiftDirection(log);
		setRenderTexture();
	}
}

void Enemy::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, &textureRect, &rect);
}

void Enemy::initRenderTexture(SDL_Renderer* renderer, Logging* log) {
	IMG_Init(SDL_INIT_EVERYTHING);
	surface = IMG_Load("Assets/Sprites/enemySheet.png");
	log->logTexture("Assets/Sprites/enemySheet.png", "enemy object");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void Enemy::setRenderTexture() {
	looper += 20;
	if (looper > 20) {
		looper = 0;
	}
	textureRect.x = looper;
	textureRect.y = lastMovement * 20;
}