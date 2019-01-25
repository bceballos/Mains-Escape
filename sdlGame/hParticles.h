#ifndef gameParticles
#define gameParticles

#include "SDL.h"
#include <vector>
#include "hVector.h"
#include "hTimer.h"

class Particle
{
public:

	int angle, longevity;
	int radius;
	float elapsedTime;

	SDL_Surface* surface;
	SDL_Texture* texture;

	Vector movementCalc;

	SDL_Rect rect;

	void init(std::vector<SDL_Texture*> textures, int x, int y, int angle, int size);
	void render(SDL_Renderer* renderer);
	void update(Timer t);
	void clearTexture();
	void randomTexture();

	float x = 0.0f;
	float y = 0.0f;

private:
	std::vector<SDL_Texture*> textures;
};

class ParticleManager {
public:
	~ParticleManager();

	std::vector<SDL_Surface*> surfaces = {};
	std::vector<SDL_Texture*> textures = {};

	Timer timer;

	std::vector<Particle*> particlesList;

	void init(SDL_Renderer* renderer, int quantity, int x, int y);
	void update();
	void remover();
	void render(SDL_Renderer* renderer);

private:


};


#endif