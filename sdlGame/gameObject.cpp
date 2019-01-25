#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "hGameObject.h"

SDL_Surface* GameObject::wallSurface = NULL;
SDL_Texture* GameObject::wallTexture = NULL;
SDL_Surface* GameObject::floorSurface = NULL;
SDL_Texture* GameObject::floorTexture = NULL;
SDL_Surface* GameObject::finishSurface = NULL;
SDL_Texture* GameObject::finishTexture = NULL;


void GameObject::setRenderTexture(SDL_Renderer* renderer, Logging* log) {
	IMG_Init(SDL_INIT_EVERYTHING);
	if (t == GameObject::Type::EMPTY || t == GameObject::Type::START) {
		if (GameObject::floorSurface == NULL) {
			GameObject::floorSurface = IMG_Load("Assets/Sprites/floortile.png");
			GameObject::floorTexture = SDL_CreateTextureFromSurface(renderer, GameObject::floorSurface);
		}

		surface = GameObject::floorSurface;
		texture = GameObject::floorTexture;

		log->logTexture("Assets/Sprites/floortile.png", "empty tile");
	}
	else if (t == GameObject::Type::WALL) {
		if (GameObject::wallSurface == NULL) {
			GameObject::wallSurface = IMG_Load("Assets/Sprites/walltile.png");
			GameObject::wallTexture = SDL_CreateTextureFromSurface(renderer, GameObject::wallSurface);
		}

		surface = GameObject::wallSurface;
		texture = GameObject::wallTexture;

		log->logTexture("Assets/Sprites/walltile.png", "wall tile");
	}
	else if (t == GameObject::Type::FINISH) {
		if (GameObject::finishSurface == NULL) {
			GameObject::finishSurface = IMG_Load("Assets/Sprites/finishtile.png");
			GameObject::finishTexture = SDL_CreateTextureFromSurface(renderer, GameObject::finishSurface);
		}

		surface = GameObject::finishSurface;
		texture = GameObject::finishTexture;
	}
}

void GameObject::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	//Change for sprites later
	//SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	//SDL_RenderDrawRect(renderer, &rect);
}

void GameObject::init(Type t,/* int r, int g, int b,*/ int x, int y, int blockSize, SDL_Renderer* renderer, Logging* log) {
	rect.x = x;
	rect.y = y;
	rect.w = blockSize;
	rect.h = blockSize;
	this->t = t;
	//this->r = r;
	//this->g = g;
	//this->b = b;
	setRenderTexture(renderer, log);
}