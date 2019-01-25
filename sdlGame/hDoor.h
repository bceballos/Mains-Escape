#ifndef gameDoor
#define gameDoor

#include <vector>

#include "hGameObject.h"

class Door : public GameObject {

public:
	SDL_Surface* surface;
	SDL_Texture* textureActive;
	SDL_Texture* textureInactive;

	void init(Type, /* int r, int g, int b,*/ int x, int y, int blockSize, SDL_Renderer* renderer);
	bool active = true;
	void setDoorState();
	void render(SDL_Renderer* renderer) override;
	void initRenderTexture(SDL_Renderer* renderer);
private:



};

#endif 