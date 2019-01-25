#ifndef gameObject
#define gameObject

#include "SDL.h"
#include "hLog.h"

class GameObject {

public:

	enum class Type { WALL, EMPTY, DOOR, ENEMY, PLAYER, START, FINISH };

	static SDL_Surface* wallSurface;
	static SDL_Texture* wallTexture;

	static SDL_Surface* floorSurface;
	static SDL_Texture* floorTexture;

	static SDL_Surface* finishSurface;
	static SDL_Texture* finishTexture;

	Type t;

	SDL_Rect rect;

	SDL_Surface* surface;
	SDL_Texture* texture;

	bool passedEmpty = true;

	void init(Type, /* int r, int g, int b,*/ int x, int y, int blockSize, SDL_Renderer* renderer, Logging* log);
	void virtual render(SDL_Renderer* renderer);
	void setRenderTexture(SDL_Renderer* renderer, Logging* log);

	int r = 0;
	int b = 255;
	int g = 0;

private:

};

#endif 