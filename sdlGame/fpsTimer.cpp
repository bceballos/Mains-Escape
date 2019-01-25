#include <iostream>

#include "hTimer.h"
#include "SDL.h"

FpsTimer::FpsTimer() {
	startTicks = 0;
}
FpsTimer::~FpsTimer()
{
}
;

void FpsTimer::resetTicksTimer() {
	startTicks = SDL_GetTicks();
}

void FpsTimer::delayTicksTimer() {
	if (getTicks() < deltaTime)
	{
		SDL_Delay((deltaTime / speed) - getTicks());
	}
}

int FpsTimer::getTicks() {
	return(SDL_GetTicks() - startTicks);
}

void FpsTimer::useless()
{
}
