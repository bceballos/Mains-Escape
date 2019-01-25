#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include "SDL.h"
#include "SDL_image.h"
#include "hGameEngine.h"
#include "hGameTimer.h"
#include "hGameObject.h"
#include "hDoor.h"
#include "hEnemy.h"
#include "hFont.h"
#include "hTimer.h"


/*
	CHECKLIST:

	-SETTINGS
	-HOW TO PLAY
	-CREATE MENU ARTWORK
	-CREATE WIN SCREEN ARTWORK: 2
		- WIN BY GETTING TO FINISH MAIN STANDING
		- END BY NOT GETTING TO FINISH MAIN FALLING

	BASICALLY DONE AUDIO: NO
*/

bool Game::init() {
	Timer initTime;
	initTime.setStart();
	TTF_Init();
	log = new Logging();
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) { //If SDL initializes / is setup right
		log->logGeneral("SDL initialized");

		window = SDL_CreateWindow("17631941 - Brennan Ceballos Pena - Games Computing - Main's Escape ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE); //Set window params and create window

		if (window != NULL) {
			log->logGeneral("Window initalized");

			SDL_SetWindowMinimumSize(window, windowWidth, windowHeight);
			renderer = SDL_CreateRenderer(window, 0, 0); //Set rendrer params and create renderer

			if (renderer != NULL) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
				log->logGeneral("Renderer initalized");
			}
			else {
				log->logGeneral("Renderer initalization failed");
			}
		}
		else {
			log->logGeneral("Window initalization failed");
		}
	}
	else {
		log->logGeneral("SDL initalization failed");
		return false; //If can't initialize set game running to false
	}

	if (SDL_Init(SDL_INIT_JOYSTICK) < 0) {
		log->logGeneral("ERROR COULD NOT INITIALIZE JOYSTICK SDL ERROR");
	} else if (SDL_NumJoysticks() < 1) {
		log->logGeneral("WARNING NO GAMEPADS CONNECTED");
	}
	else {
		gamePad = SDL_JoystickOpen(0); 
		log->logGeneral("GamePad loaded");
		if (gamePad == NULL) {
			log->logGeneral("ERROR COULD NOT DETECT GAME PAD");
		}
	}

	keys.load("Settings/controls.json");
	log->logGeneral("keyboard input loaded");
	gameRunning = true;
	menuRunning = true;
	isRunning = true;
	initFonts();
	setPausedTexture();
	state = MENU;
	initAudio();
	if (Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(bgMusic, -1);
	}
	else {
		Mix_HaltMusic();
	}
	log->logInit("INIT TIME", "initialize the game", initTime.getTime());
	return true; //Set the game running to true */
}

void Game::build() {
	Timer w;
	w.setStart();
	worldTiles.clear();
	enemyObjs.clear();
	doorTiles.clear();
	for (int h = 0; h < windowColumns; h++) {

		for (int w = 0; w < windowRows; w++) {
			GameObject* tile = new GameObject();
			Door* door = new Door();
			Enemy* enemy = new Enemy();

			switch (worldInts[(h*windowRows) + w])
			{
			case 0:
				tile->init(GameObject::Type::EMPTY, w*blockSize, h*blockSize, blockSize, renderer, log);
				worldTiles.push_back(tile);
				break;
			case 1:
				tile->init(GameObject::Type::START, w*blockSize, h*blockSize, blockSize, renderer, log);
				worldTiles.push_back(tile);
				player.init(GameObject::Type::PLAYER, w*blockSize, h*blockSize, blockSize, chosenHealth, renderer, log);
				break;
			case 2:
				tile->init(GameObject::Type::WALL, w*blockSize, h*blockSize, blockSize, renderer, log);
				worldTiles.push_back(tile);
				break;
			case 3:
				door->init(Door::Type::DOOR, w*blockSize, h*blockSize, blockSize, renderer);
				doorTiles.push_back(door);
				worldTiles.push_back(door);
				break;
			case 4:
				tile->init(GameObject::Type::FINISH, w*blockSize, h*blockSize, blockSize,renderer, log);
				worldTiles.push_back(tile);
				break;
			case 5:
				enemy->init(GameObject::Type::ENEMY, w*blockSize, h*blockSize, blockSize, renderer, log);
				enemyObjs.push_back(enemy);
				tile->init(GameObject::Type::EMPTY, w*blockSize, h*blockSize, blockSize, renderer, log);
				worldTiles.push_back(tile);

			default:
				break;
			}
		}

	}
	
	log->logInit("WORLD INIT", "build the world", w.getTime());
}

void Game::initFonts() {
	health = new Font();
	time = new Font();
	score = new Font();
	play = new Font();
	settings = new Font();
	howToPlay = new Font();
	easyText = new Font();
	normalText = new Font();
	hardText = new Font();
	audioVolume = new Font();
	audioVolumeInt = new Font();
	audioIncreaseVol = new Font();
	audioDecreaseVol = new Font();
	muteAudio = new Font();
	muteAudioText = new Font();
	muteSFX = new Font();
	muteSFXText = new Font();
	howToPlayText = new Font();
	backButton = new Font();
	quit = new Font();
	returnToMenu = new Font();
	endScore = new Font();
	keyboardInputs = new Font();
	controllerInputs = new Font();
	pauseAudioVolume = new Font();
	pauseAudioVolumeInt = new Font();
	pauseAudioIncreaseVol = new Font();
	pauseAudioDecreaseVol = new Font();
	pauseMuteAudio = new Font();
	pauseMuteAudioText = new Font();
	pauseMuteSFX = new Font();
	pauseMuteSFXText = new Font();
	keyboardInputs->init(FONT_PATH, 25, 255,255,255, 25 ,530,750);
	controllerInputs->init(FONT_PATH, 35, 255, 255, 255, 25, 580, 750);
	backButton->init(FONT_PATH, 72, 255, 255, 255, ((windowWidth - 200) / 2), 530, 200);
	play->init(FONT_PATH, 72, 255, 255, 255, ((windowWidth - 200) / 2), 230, 200);
	settings->init(FONT_PATH, 72, 255, 255, 255, ((windowWidth - 300) / 2), 330, 300);
	howToPlay->init(FONT_PATH, 72, 255, 255, 255, ((windowWidth - 400) / 2), 430, 400);
	menuItems.push_back(play);
	menuItems.push_back(settings);
	menuItems.push_back(howToPlay);
	easyText->init(FONT_PATH, 72, 255, 255, 255, ((windowWidth - 200) / 2), 230, 200);
	normalText->init(FONT_PATH, 72, 255, 255, 255, ((windowWidth - 200) / 2), 330, 200);
	hardText->init(FONT_PATH, 72, 255, 255, 255, ((windowWidth - 200) / 2), 430, 200);
	difficultyItems.push_back(easyText);
	difficultyItems.push_back(normalText);
	difficultyItems.push_back(hardText);
	difficultyItems.push_back(backButton);
	audioVolume->init(FONT_PATH, 72, 255, 255, 255, ((windowWidth - 500) / 2), 230, 300);
	audioIncreaseVol->init(FONT_PATH, 72, 255, 255, 255, ((windowWidth + 50) / 2) + 144, 230, 50);
	audioDecreaseVol->init(FONT_PATH, 72, 255, 255, 255, ((windowWidth + 50) / 2) + 28, 230, 50);
	audioVolumeInt->init(FONT_PATH, 72, 255, 255, 255, ((windowWidth + 50) / 2) + 72, 230, 72);
	muteAudio->init(FONT_PATH, 72, 255, 255, 255, ((windowWidth - 500) / 2), 330, 200);
	muteAudioText->init(FONT_PATH, 72, 255, 255, 255, ((windowWidth + 50) / 2)+72, 330, 72);
	muteSFX->init(FONT_PATH, 72, 255, 255, 255, ((windowWidth - 500) / 2), 430, 200);
	muteSFXText->init(FONT_PATH, 72, 255, 255, 255, ((windowWidth + 50) / 2)+72, 430, 72);
	settingsItems.push_back(audioIncreaseVol);
	settingsItems.push_back(audioDecreaseVol);
	settingsItems.push_back(muteAudioText);
	settingsItems.push_back(muteSFXText);
	settingsItems.push_back(backButton);
	howToPlayText->init(FONT_PATH, 72, 255, 255, 255, ((windowWidth - 500) / 2), 230, 500);
	howtoItems.push_back(backButton);
	endScore->init(FONT_PATH, 72, 255, 255, 255, ((windowWidth - 200) / 2), 230, 200);
	quit->init(FONT_PATH, 72, 255, 255, 255, 100, 530, 200);
	returnToMenu->init(FONT_PATH, 72, 255, 255, 255, 450, 530, 300);
	scoreItems.push_back(quit);
	scoreItems.push_back(returnToMenu);
	health->init(FONT_PATH, 60, 255, 255, 255, 0, windowHeight - 60, 200);
	time->init(FONT_PATH, 60, 255, 255, 255, 300, windowHeight - 60, 200);
	score->init(FONT_PATH, 60, 255, 255, 255, 600, windowHeight - 60, 200);
	pauseAudioVolume->init(FONT_PATH, 60, 255, 255, 255, 25, 230, 175);
	pauseAudioIncreaseVol->init(FONT_PATH, 60, 255, 255, 255, 300, 230, 30);
	pauseAudioVolumeInt->init(FONT_PATH, 60, 255, 255, 255, 240, 230, 50);
	pauseAudioDecreaseVol->init(FONT_PATH, 60, 255, 255, 255, 200, 230, 30);
	pauseMuteAudio->init(FONT_PATH, 60, 255, 255, 255, 25, 330, 175);
	pauseMuteAudioText->init(FONT_PATH, 60, 255, 255, 255, 227, 330, 72);
	pauseMuteSFX->init(FONT_PATH, 60, 255, 255, 255, 25, 430, 175);
	pauseMuteSFXText->init(FONT_PATH, 60, 255, 255, 255, 227, 430, 72);
	pauseMenuItems.push_back(pauseAudioIncreaseVol);
	pauseMenuItems.push_back(pauseAudioDecreaseVol);
	pauseMenuItems.push_back(pauseMuteAudioText);
	pauseMenuItems.push_back(pauseMuteSFXText);
}

void Game::run() {
	readFile();
	build();
	isRunning = true;
	player.score = 0;
	GameTimer fpsLock;
	Timer t;
	gameDuration = 0;

	// Switcher, no switching!
	while (isRunning) {
		t.setStart();

		fpsLock.resetTicksTimer();
		if (!paused) {
			input();
			pauseIndex = 8;
		}
		else {
			state = PAUSE;
			menuInput();
		}

		if (!paused) {
			update();
			lateUpdate();
		}

		render();

		fpsLock.gameLoopDelay();

		if (!paused) {
			gameDuration += t.getTime();
		}
		log->logPerformance(t.getTime());
		if (60 - (gameDuration / 1000) <= 0) {
			isRunning = false;
			break;
		}
	}
}

void Game::update() {
	player.update(log);
	
	for (Enemy* enemy : enemyObjs) {
		enemy->update(log);
	}

	float now = SDL_GetTicks();
	if ((now - lastDoorChange) >= 2500) {
		lastDoorChange = now;
		for (Door* door : doorTiles) {
			door->setDoorState();
		}
	}
	
}

void Game::lateUpdate() {

	player.lateUpdate(worldTiles, doorTiles, enemyObjs, renderer, log, (60 - (gameDuration / 1000)));

	for (Enemy* enemy : enemyObjs) {
		enemy->lateUpdate(worldTiles, doorTiles, log);
	}
}

void Game::render() {
	Timer renderTime;
	renderTime.setStart();
	SDL_RenderClear(renderer); //Clear the renderer's buffer

	for (GameObject* object : worldTiles) {
		object->render(renderer);
	}

	for (Enemy* enemy : enemyObjs) {
		enemy->render(renderer);
	}

	player.render(renderer);

	std::string healthText = "HEALTH: " + std::to_string(player.health);
	std::string timeText = std::to_string(60 - (gameDuration / 1000));
	std::string scoreText = "SCORE: " + std::to_string(player.score);

	health->render(renderer, healthText);
	time->render(renderer, timeText);
	score->render(renderer, scoreText);

	if (paused) {
		SDL_RenderCopy(renderer, pausedTexture, NULL, &pausedRect);
		//RENDER SETTINGS MENU
		//AUDIO < 10 >
		//MUTE AUDIO: OFF
		//MUTE SFX: OFF
		//RENDER BACK BUTTON
		pauseAudioVolume->render(renderer, "AUDIO VOLUME ");
		pauseAudioDecreaseVol->render(renderer, "<");
		pauseAudioVolumeInt->render(renderer, std::to_string(volume));
		pauseAudioIncreaseVol->render(renderer, ">");
		pauseMuteAudio->render(renderer, "MUSIC ");
		if (audioToggle) { pauseMuteAudioText->render(renderer, "OFF"); }
		else { pauseMuteAudioText->render(renderer, "ON"); }
		pauseMuteSFX->render(renderer, "SFX ");
		if (sfxToggle) { pauseMuteSFXText->render(renderer, "OFF"); }
		else { pauseMuteSFXText->render(renderer, "ON"); }

		if (state == PAUSE) {
			for (int i = 0; i < pauseMenuItems.size(); i++) {
				if (i == pauseIndex) {
					pauseMenuItems[i]->setColor(150, 190, 255);
				}
				else {
					pauseMenuItems[i]->setColor(255, 255, 255);
				}
			}

		}
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderPresent(renderer);
	log->logRenderTime(renderTime.getTime());
}

void Game::input() {
	SDL_Event event; //Check events 
	while (SDL_PollEvent(&event) != 0) { 

		switch (event.type) {
		case SDL_QUIT:
			clean();
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				windowResize();
			}
			break;

		case SDL_JOYBUTTONDOWN:
			if (event.jbutton.button == 7) {
				paused = !paused;
				std::cout << paused << std::endl;
			}
			else if (event.jbutton.button == 6 && !fullScreen) {
				SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
				fullScreen = true;
			}
			else if (event.jbutton.button == 6 && fullScreen) {
				SDL_SetWindowFullscreen(window, 0);
				fullScreen = false;
			}
			break;
		default:
			if ((event.key.keysym.sym == keys.fullscreen)&& !fullScreen && event.type == SDL_KEYDOWN ) {
				log->logInput("KEYDOWN",event.key.timestamp, SDL_Keycode(event.key.keysym.sym));
				SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
				log->logGeneral("window has been scalled to fullscreen");
				fullScreen = true;
			}
			else if ((event.key.keysym.sym == keys.fullscreen) && fullScreen && event.type == SDL_KEYDOWN) {
				log->logInput("KEYDOWN", event.key.timestamp, SDL_Keycode(event.key.keysym.sym));
				SDL_SetWindowFullscreen(window, 0);
				log->logGeneral("window has been scalled down from fullscreen");
				fullScreen = false;
			}
			if (event.key.keysym.sym == keys.log && event.type == SDL_KEYDOWN) {
				log->log = !log->log;
			}
			if ((event.key.keysym.sym == keys.pause && (event.type == SDL_KEYDOWN))) {
				paused = !paused;
			}
			else if (!paused) {
				player.input(event, log, keys, gamePad);
			}
			break;
		}

	}
}

void Game::clean() {
	log->logGeneral("game closed, objects destroyed, game memory cleaned");
	SDL_JoystickClose(gamePad);
	gamePad = NULL;
	delete health;
	delete score;
	delete time;
	delete settings;
	delete howToPlay;
	delete easyText;
	delete normalText;
	delete hardText;
	delete audioVolume;
	delete audioVolumeInt;
	delete audioIncreaseVol;
	delete audioDecreaseVol;
	delete muteAudio;
	delete muteAudioText;
	delete muteSFX;
	delete muteSFXText;
	delete howToPlayText;
	delete backButton;
	delete gamePad;
	delete log;
	TTF_Quit();
	IMG_Quit();
	Mix_FreeChunk(player.hurtSFX);
	Mix_FreeChunk(player.particleSFX);
	Mix_FreeMusic(bgMusic);
	Mix_CloseAudio();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	exit(0);
}

void Game::readFile() {
	if (!fileHasBeenRead) {
		std::string line;

		std::ifstream f("Assets/Maps/world.txt");

		if (f.is_open())
		{
			log->logGeneral("world map file opened");
			while (std::getline(f, line))
			{
				for (char num : line) {
					if (!isspace(num)) {
						worldInts.push_back(num - '0');
					}
				}
			}
			f.close();
		}
		else {
			log->logGeneral("world map file unable to be opened");
		}
	}
}

void Game::windowResize() {
	SDL_RenderSetLogicalSize(renderer, windowWidth, windowHeight);
	SDL_GetWindowSize(window, &scaleTextHitBoxX, &scaleTextHitBoxY);
	log->logGeneral("window has been resized to "+std::to_string(scaleTextHitBoxX) +", "+ std::to_string(scaleTextHitBoxY)+"from 800, 660");
}

void Game::runMenu() {
	GameTimer fpsLock;
	selectedMenuIndex = NULL;
	selectedScoreIndex = NULL;
	menuRunning = true;
	while (menuRunning) {
		fpsLock.resetTicksTimer();

		menuInput();
		menuUpdate();
		menuRender();

		fpsLock.gameLoopDelay();
	}
	menuRunning = false;
}

void Game::menuInput() {
	SDL_Event event; //Check events 
	while (SDL_PollEvent(&event) != 0) {

		switch (event.type) {
		case SDL_QUIT:
			clean();
			gameRunning = false;
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				windowResize();
			}
			break;
		case SDL_MOUSEMOTION:
			x = event.motion.x;
			y = event.motion.y;
			if (state == MENU) {
				for (int i = 0; i < menuItems.size(); i++) {
					if (x >= menuItems[i]->rect.x && x <= (menuItems[i]->rect.x + menuItems[i]->rect.w) && y >= menuItems[i]->rect.y && y <= (menuItems[i]->rect.y + menuItems[i]->rect.h)) {
						menuIndex = i;
					}
				}
			}
			else if (state == PLAY) {
				for (int i = 0; i < difficultyItems.size(); i++) {
					if (x >= difficultyItems[i]->rect.x && x <= (difficultyItems[i]->rect.x + difficultyItems[i]->rect.w) && y >= difficultyItems[i]->rect.y && y <= (difficultyItems[i]->rect.y + difficultyItems[i]->rect.h)) {
						difficultyIndex = i;
					}
				}
			}
			else if (state == SETTINGS) {
				for (int i = 0; i < settingsItems.size(); i++) {
					if (x >= settingsItems[i]->rect.x && x <= (settingsItems[i]->rect.x + settingsItems[i]->rect.w) && y >= settingsItems[i]->rect.y && y <= (settingsItems[i]->rect.y + settingsItems[i]->rect.h)) {
						settingsIndex = i;
					}
				}
			}
			else if (state == HOWTO) {
				for (int i = 0; i < howtoItems.size(); i++) {
					if (x >= howtoItems[i]->rect.x && x <= (howtoItems[i]->rect.x + howtoItems[i]->rect.w) && y >= howtoItems[i]->rect.y && y <= (howtoItems[i]->rect.y + howtoItems[i]->rect.h)) {
						howtoIndex = i;
					}
				}
			}
			else if (state == SCORE) {
				for (int i = 0; i < scoreItems.size(); i++) {
					if (x >= scoreItems[i]->rect.x && x <= (scoreItems[i]->rect.x + scoreItems[i]->rect.w) && y >= scoreItems[i]->rect.y && y <= (scoreItems[i]->rect.y + scoreItems[i]->rect.h)) {
						endScoreIndex = i;
					}
				}
			}
			else if (state == PAUSE) {
				for (int i = 0; i < pauseMenuItems.size(); i++) {
					if (x >= pauseMenuItems[i]->rect.x && x <= (pauseMenuItems[i]->rect.x + pauseMenuItems[i]->rect.w) && y >= pauseMenuItems[i]->rect.y && y <= (pauseMenuItems[i]->rect.y + pauseMenuItems[i]->rect.h)) {
						pauseIndex = i;
					}
				}
			}

			break;
		default:
			if ((event.key.keysym.sym == keys.fullscreen) && !fullScreen && event.type == SDL_KEYDOWN) {
				log->logInput("KEYDOWN", event.key.timestamp, SDL_Keycode(event.key.keysym.sym));
				SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
				log->logGeneral("window has been scalled to fullscreen");
				fullScreen = true;
			}
			else if ((event.key.keysym.sym == keys.fullscreen) && fullScreen && event.type == SDL_KEYDOWN) {
				log->logInput("KEYDOWN", event.key.timestamp, SDL_Keycode(event.key.keysym.sym));
				SDL_SetWindowFullscreen(window, 0);
				log->logGeneral("window has been scalled down from fullscreen");
				fullScreen = false;
			}
			if (event.key.keysym.sym == keys.log && event.type == SDL_KEYDOWN) {
				log->log = !log->log;
			}
			if (event.key.keysym.sym == keys.forward && event.type == SDL_KEYDOWN) {
				if (state == MENU) {
					menuIndex = (menuIndex + 1) % menuItems.size();
				}
				else if (state == PLAY) {
					difficultyIndex = (difficultyIndex + 1) % difficultyItems.size();
				}
				else if (state == SETTINGS) {
					settingsIndex = (settingsIndex + 1) % settingsItems.size();
				}
				else if (state == HOWTO) {
					howtoIndex = (howtoIndex + 1) % howtoItems.size();
				}
				else if (state == SCORE) {
					endScoreIndex = (endScoreIndex + 1) % scoreItems.size();
				}
				else if (state == PAUSE) {
					pauseIndex = (pauseIndex + 1) % pauseMenuItems.size();
				}
				
			}
			if (event.key.keysym.sym == keys.backward && event.type == SDL_KEYDOWN) {
				if (state == MENU) {
					if ((menuIndex - 1) < 0) {
						menuIndex = menuItems.size() - 1;
					}
					else {
						menuIndex--;
					}
				}
				else if (state == PLAY) {
					if ((difficultyIndex - 1) < 0) {
						difficultyIndex = difficultyItems.size() - 1;
					}
					else {
						difficultyIndex--;
					}
				}
				else if (state == SETTINGS) {
					if ((settingsIndex - 1) < 0) {
						settingsIndex = settingsItems.size() - 1;
					}
					else {
						settingsIndex--;
					}
				}
				else if (state == HOWTO) {
					if ((howtoIndex - 1) < 0) {
						howtoIndex = howtoItems.size() - 1;
					}
					else {
						howtoIndex--;
					}
				}
				else if (state == SCORE) {
					if ((endScoreIndex - 1) < 0) {
						endScoreIndex = scoreItems.size() - 1;
					}
					else {
						endScoreIndex--;
					}
				}
				else if (state == PAUSE) {
					if ((pauseIndex - 1) < 0) {
						pauseIndex = pauseMenuItems.size() - 1;
					}
					else {
						pauseIndex--;
					}
				}

			}
			if (event.key.keysym.sym == keys.enter && event.type == SDL_KEYDOWN) {
				selectItemFunctionality();
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				handleMouseClicks(event.button);
			}
			if (event.key.keysym.sym == keys.pause && event.type == SDL_KEYDOWN) {
				paused = false;
				state = PLAY;
			}
			break;
		}

	}
}

void Game::menuUpdate() {
	if (state == MENU) {
		for (int i = 0; i < menuItems.size(); i++) {
			if (i == menuIndex) {
				menuItems[i]->setColor(150, 190, 255);
				
			}
			else {
				menuItems[i]->setColor(255, 255, 255);

			}
		}
	}
	if (state == PLAY) {
		for (int i = 0; i < difficultyItems.size(); i++) {
			if (i == difficultyIndex) {
				difficultyItems[i]->setColor(150, 190, 255);
			}
			else {
				difficultyItems[i]->setColor(255, 255, 255);

			}
		}
	}
	if (state == SETTINGS) {
		for (int i = 0; i < settingsItems.size(); i++) {
			if (i == settingsIndex) {
				settingsItems[i]->setColor(150, 190, 255);
			}
			else {
				settingsItems[i]->setColor(255, 255, 255);

			}
		}
	}
	if (state == HOWTO) {
		for (int i = 0; i < howtoItems.size(); i++) {
			if (i == howtoIndex) {
				howtoItems[i]->setColor(150, 190, 255);
				
			}
			else {
				howtoItems[i]->setColor(255, 255, 255);
			}
		}
		
	}
}

void Game::menuRender() {
	Timer renderTime;
	renderTime.setStart();
	SDL_RenderClear(renderer); //Clear the renderer's buffer
	SDL_RenderCopy(renderer, menuTexture, NULL, &menuRect);

	if (state == MENU) {
		play->render(renderer, "PLAY");
		settings->render(renderer, "SETTINGS");
		howToPlay->render(renderer, "HOW TO PLAY");
		keyboardInputs->render(renderer, "Keyboard Inputs - Forward: " + std::string(SDL_GetKeyName(keys.forward)) + ", Down: " + std::string(SDL_GetKeyName(keys.backward)) + ", Left: " + std::string(SDL_GetKeyName(keys.left)) + ", Right: " + std::string(SDL_GetKeyName(keys.right)) + ", Sprint: " + std::string(SDL_GetKeyName(keys.sprint)) + ", Select: " + std::string(SDL_GetKeyName(keys.enter))+ ", Pause: " + std::string(SDL_GetKeyName(keys.pause)) + ", FullScreen: " + std::string(SDL_GetKeyName(keys.fullscreen)));
		controllerInputs->render(renderer, "Controller Inputs - Left Joystick: Movement, Left Trigger: Sprint, Pause: Start Button, Fullscreen: Back Button");
	}

	if (state == PLAY) {
		//RENDER
		//EASY
		//NORMAL
		//HARD
		easyText->render(renderer, "EASY");
		normalText->render(renderer, "NORMAL");
		hardText->render(renderer, "HARD");
		backButton->render(renderer, "BACK");
	}

	if (state == SETTINGS) {
		//RENDER SETTINGS MENU
		//AUDIO < 10 >
		//MUTE AUDIO: OFF
		//MUTE SFX: OFF
		//RENDER BACK BUTTON
		audioVolume->render(renderer, "AUDIO VOLUME ");
		audioDecreaseVol->render(renderer, "<");
		audioVolumeInt->render(renderer, std::to_string(volume));
		audioIncreaseVol->render(renderer, ">");
		muteAudio->render(renderer, "MUSIC ");
		if (audioToggle) { muteAudioText->render(renderer, "OFF"); }
		else { muteAudioText->render(renderer, "ON");  }
		muteSFX->render(renderer, "SFX ");
		if (sfxToggle) { muteSFXText->render(renderer, "OFF"); }
		else { muteSFXText->render(renderer, "ON"); }
		backButton->render(renderer, "BACK");
	}

	if (state == HOWTO) {
		// RENDER HOW TO PLAY MENU ICON
		// RENDER BACK BUTTON
		SDL_RenderCopy(renderer, howtoTexture, NULL, &menuRect);
		backButton->render(renderer, "BACK");
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderPresent(renderer);
	log->logRenderTime(renderTime.getTime());
}

void Game::setPausedTexture() {
	howtoSurface = IMG_Load("Assets/Sprites/howtoscreen.png");
	pausedSurface = IMG_Load("Assets/Sprites/pausedscreen.png");
	menuSurface = IMG_Load("Assets/Sprites/menuscreen.png");
	pausedTexture = SDL_CreateTextureFromSurface(renderer, pausedSurface);
	menuTexture = SDL_CreateTextureFromSurface(renderer, menuSurface);
	howtoTexture = SDL_CreateTextureFromSurface(renderer, howtoSurface);
	SDL_FreeSurface(pausedSurface);
	SDL_FreeSurface(menuSurface);
	SDL_FreeSurface(howtoSurface);
	pausedRect.w = windowWidth;
	pausedRect.h = windowHeight - 60;
	menuRect.w = windowWidth;
	menuRect.h = windowHeight;
}

void Game::selectItemFunctionality() {
	if (state == MENU) {
		selectedMenuIndex = menuIndex;
		switch (selectedMenuIndex) {
		case 0:
			state = PLAY;
			break;
		case 1:
			state = SETTINGS;
			break;
		case 2:
			state = HOWTO;
			break;
		default:
			break;
		}
		if (!sfxToggle) { Mix_PlayChannel(-1, menuHover, 0); }
	}
	else if (state == PLAY) {
		selectedMenuIndex = difficultyIndex;
		switch (selectedMenuIndex) {
		case 0:
			chosenHealth = easyHealth;
			menuRunning = false;
			break;
		case 1:
			chosenHealth = normalHealth;
			menuRunning = false;
			break;
		case 2:
			chosenHealth = hardHealth;
			menuRunning = false;
			break;
		case 3:
			state = MENU;
			break;
		default:
			break;
		}
		if (!sfxToggle) { Mix_PlayChannel(-1, menuHover, 0); }
	}
	else if (state == SETTINGS) {
		selectedMenuIndex = settingsIndex;
		switch (selectedMenuIndex) {
		case 0:
			volume++;
			if (volume > 100) {
				volume = 0;
			}
			interpVol = ceil(volume * 2.55);
			Mix_VolumeMusic(interpVol);
			Mix_VolumeChunk(menuHover, interpVol);
			Mix_VolumeChunk(player.hurtSFX, interpVol);
			Mix_VolumeChunk(player.particleSFX, interpVol);
			break;
		case 1:
			volume--;
			if (volume < 0) {
				volume = 100;
			}
			interpVol = ceil(volume * 2.55);
			Mix_VolumeMusic(interpVol);
			Mix_VolumeChunk(menuHover, interpVol);
			Mix_VolumeChunk(player.hurtSFX, interpVol);
			Mix_VolumeChunk(player.particleSFX, interpVol);
			break;
		case 2:
			audioToggle = !audioToggle;
			if (Mix_PlayingMusic() == 0) {
				Mix_PlayMusic(bgMusic, -1);
			}
			else {
				Mix_HaltMusic();
			}
			break;
		case 3:
			sfxToggle = !sfxToggle;
			player.sfxToggle = sfxToggle;
			break;
		case 4:
			state = MENU;
			break;
		default:
			break;
		}
		if (!sfxToggle) { Mix_PlayChannel(-1, menuHover, 0); }
	}
	else if (state == HOWTO) {
		selectedMenuIndex = howtoIndex;
		switch (selectedMenuIndex) {
		case 0:
			state = MENU;
			break;
		default:
			break;
		}
	}
	else if (state == SCORE) {
		selectedScoreIndex = endScoreIndex;
		switch (selectedScoreIndex) {
		case 0:
			gameRunning = false;
			menuRunning = false;
			break;
		case 1:
			menuRunning = false;
			break;
		default:
			break;
		}
	}
	else if (state == PAUSE) {
		selectedMenuIndex = pauseIndex;
		switch (selectedMenuIndex) {
		case 0:
			volume++;
			if (volume > 100) {
				volume = 0;
			}
			interpVol = ceil(volume * 2.55);
			Mix_VolumeMusic(interpVol);
			Mix_VolumeChunk(menuHover, interpVol);
			Mix_VolumeChunk(player.hurtSFX, interpVol);
			Mix_VolumeChunk(player.particleSFX, interpVol);
			break;
		case 1:
			volume--;
			if (volume < 0) {
				volume = 100;
			}
			interpVol = ceil(volume * 2.55);
			Mix_VolumeMusic(interpVol);
			Mix_VolumeChunk(menuHover, interpVol);
			Mix_VolumeChunk(player.hurtSFX, interpVol);
			Mix_VolumeChunk(player.particleSFX, interpVol);
			break;
		case 2:
			audioToggle = !audioToggle;
			if (Mix_PlayingMusic() == 0) {
				Mix_PlayMusic(bgMusic, -1);
			}
			else {
				Mix_HaltMusic();
			}
			break;
		case 3:
			sfxToggle = !sfxToggle;
			player.sfxToggle = sfxToggle;
			break;
		default:
			break;
		}
		if (!sfxToggle) { Mix_PlayChannel(-1, menuHover, 0); }
	}
}

void Game::handleMouseClicks(SDL_MouseButtonEvent &button) {
	if (button.button == SDL_BUTTON_LEFT && button.state == SDL_PRESSED) {
		selectItemFunctionality();
	}
}

void Game::endScoreScreen() {
	GameTimer fpsLock;
	selectedMenuIndex = 8;
	menuRunning = true;
	while (menuRunning) {
		fpsLock.resetTicksTimer();

		menuInput();
		endScoreUpdate();
		endScoreRender();

		fpsLock.gameLoopDelay();
	}
}

void Game::endScoreUpdate() {
	if (state == SCORE) {
		for (int i = 0; i < scoreItems.size(); i++) {
			if (i == endScoreIndex) {
				scoreItems[i]->setColor(150, 190, 255);
			}
			else {
				scoreItems[i]->setColor(255, 255, 255);
			}
		}
	}
}

void Game::endScoreRender() {
	Timer renderTime;
	renderTime.setStart();
	SDL_RenderClear(renderer); //Clear the renderer's buffer
	SDL_RenderCopy(renderer, menuTexture, NULL, &menuRect);
	endScore->render(renderer, "SCORE: " + std::to_string(player.score));
	quit->render(renderer, "QUIT");
	returnToMenu->render(renderer, "MAIN MENU");

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderPresent(renderer);
	log->logRenderTime(renderTime.getTime());
}

void Game::initAudio() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		log->logGeneral("Audio has not been found");
	}
	else {
		log->logGeneral("Audio has been loaded");
		bgMusic = Mix_LoadMUS("Assets/Audio/backgroundsong.wav");
		menuHover = Mix_LoadWAV("Assets/Audio/menuselect.wav");
		player.hurtSFX = Mix_LoadWAV("Assets/Audio/playerhurt.wav");
		player.particleSFX = Mix_LoadWAV("Assets/Audio/particleeffect.wav");
	}
	Mix_VolumeMusic(interpVol);
	Mix_VolumeChunk(menuHover, interpVol);
	Mix_VolumeChunk(player.hurtSFX, interpVol);
	Mix_VolumeChunk(player.particleSFX, interpVol);
}