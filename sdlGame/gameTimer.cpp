#include <iostream>
#include "SDL.h"
#include "hGameTimer.h"

GameTimer::GameTimer() {
	startTicks = 0;
}
GameTimer::~GameTimer()
{
}

void GameTimer::resetTicksTimer() {
	startTicks = SDL_GetTicks();
}

int GameTimer::getTicks() {
	return(SDL_GetTicks() - startTicks);
}

void GameTimer::gameLoopDelay() {
	if (getTicks() < deltaTime)
	{
		SDL_Delay((deltaTime / speed) - getTicks());
	}
}


