#include <iostream>
#include <stdlib.h>

#include "SDL_image.h"
#include "hDoor.h"

void Door::init(Type t,/* int r, int g, int b,*/ int x, int y, int blockSize, SDL_Renderer* renderer) {
	rect.x = x;
	rect.y = y;
	rect.w = blockSize;
	rect.h = blockSize;
	this->t = t;
	//this->r = r;
	//this->g = g;
	//this->b = b;
	initRenderTexture(renderer);
}

void Door::initRenderTexture(SDL_Renderer* renderer) {
	IMG_Init(SDL_INIT_EVERYTHING);
	surface = IMG_Load("Assets/Sprites/doorActive.png");
	textureActive = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	surface = IMG_Load("Assets/Sprites/doorInactive.png");
	textureInactive = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void Door::setDoorState() {
	
	int state = rand() % 2 + 1;

	if (state == 1) {
		active = true;
	}
	else {
		active = false;
	}

}

void Door::render(SDL_Renderer* renderer) {
	if (active) {
		SDL_RenderCopy(renderer, textureActive, NULL, &rect);
	}
	else {
		SDL_RenderCopy(renderer, textureInactive, NULL, &rect);
	}

}
