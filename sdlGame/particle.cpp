#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "SDL_image.h"
#include "hParticles.h"
#include "hVector.h"

void Particle::init(std::vector<SDL_Texture*> textures,  int x, int y, int angle, int size) {
	this->angle = angle;
	this->textures = textures;
	//this->velocity = velocity;
	randomTexture();
	this->x = x+7.5f;
	this->y = y+7.5f;
	rect.w = size;
	rect.h = size;
	movementCalc.calculateVector(angle);
}

void Particle::clearTexture() {
	//SDL_FreeSurface(surface);
	//SDL_DestroyTexture(texture);
}

void Particle::randomTexture() {
	texture = textures[rand() % textures.size()];
}

void Particle::render(SDL_Renderer* renderer) {
	SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}

void Particle::update(Timer t) {
	randomTexture();
	x += ((movementCalc.normX) + sin(t.getTime()/60));
	y += ((movementCalc.normY) + sin(t.getTime() / 60));

	rect.x = x;
	rect.y = y;
}

void ParticleManager::init(SDL_Renderer* renderer, int quantity, int x, int y) {
	IMG_Init(SDL_INIT_EVERYTHING);
	std::vector<std::string> assetpaths = {
		"Assets/Sprites/shimmer.png" , "Assets/Sprites/blue.png",
		"Assets/Sprites/green.png", "Assets/Sprites/red.png"
	};

	for (int i = 0; i < assetpaths.size(); i++)
	{
		surfaces.push_back(IMG_Load(assetpaths[i].c_str()));
		textures.push_back(SDL_CreateTextureFromSurface(renderer, surfaces[i]));
	}

	int angle = 0;

	for (int i = 0; i < quantity; i++) {
		particlesList.push_back(new Particle());
		particlesList[i]->init(textures, x, y, angle, 5);
		angle += (360 /quantity);
	}
	timer.setStart();
}

ParticleManager::~ParticleManager()
{
	while ((int)textures.size() != 0)
	{
		delete textures[0];
		delete surfaces[0];

		textures.erase(textures.begin());
		surfaces.erase(surfaces.begin());
	}
}

void ParticleManager::update() {
	for (int i = 0; i < particlesList.size(); i++) {
		particlesList[i]->update(timer);
	}
	remover();
}

void ParticleManager::remover() {
	if (ceil(timer.getTime() / 1000) >= 2) {
		for (int i = 0; i < particlesList.size(); i++) {
			particlesList[i]->clearTexture();
			delete particlesList[i];
		}
		particlesList.clear();
	}
}

void ParticleManager::render(SDL_Renderer* renderer)
{
	for (int i = 0; i < particlesList.size(); i++) {
		particlesList[i]->render(renderer);
	}
}