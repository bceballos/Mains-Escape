#ifndef gameEnemy
#define gameEnemy
#include <vector>

#include "hGameObject.h"
#include "hDoor.h"

class Enemy : public GameObject{

public:

	enum Direction { FORWARD, LEFT, RIGHT, BACKWARDS };
	Direction enemyMove = FORWARD;

	SDL_Rect temp;
	SDL_Rect textureRect;

	float lastMovementTime = 0.0f;

	void randomMove();
	void update(Logging* log);
	void lateUpdate(std::vector<GameObject*> tiles, std::vector<Door*> doors, Logging* log);
	void init(Type t,/* int r, int g, int b,*/ int x, int y, int blockSize, SDL_Renderer* renderer, Logging* log);
	void shiftDirection(Logging* log);
	void render(SDL_Renderer* renderer) override;
	void initRenderTexture(SDL_Renderer* renderer, Logging* log);
	void setRenderTexture();

	int lastMovement;
	int looper = 0;

private:




};

#endif 