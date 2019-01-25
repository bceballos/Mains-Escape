#ifndef gamePlayer
#define gamePlayer

#include <vector>

#include "hGameObject.h"
#include "hParticles.h"
#include "hDoor.h"
#include "hEnemy.h"
#include "hLog.h"
#include "hKeys.h"

class Player : public GameObject {

public:

	enum Direction { FORWARD, LEFT, RIGHT, BACKWARDS };
	enum Movement { NONE, MOVING };

	Movement playerMove = NONE;

	std::vector<Direction> keyboardPresses;

	SDL_Rect temp;
	SDL_Rect textureRect;
	int blockSize;

	SDL_Surface* surface;
	SDL_Texture* texture;

	ParticleManager* particleEffect = NULL;


	void input(SDL_Event movement, Logging* log, Keys keys, SDL_Joystick* gamePad);
	void update(Logging* log);
	void lateUpdate(std::vector<GameObject*> tiles, std::vector<Door*> doors, std::vector<Enemy*> &enemy, SDL_Renderer* renderer, Logging* log, float endTime);
	void init(Type t, /*int r, int g, int b,*/ int x, int y, int blockSize, int health, SDL_Renderer* renderer, Logging* log);
	void render(SDL_Renderer* renderer) override;
	void initRenderTexture(SDL_Renderer* renderer);
	void setRenderTexture();
	void shiftDirection(Logging* log);

	bool invulnerable;
	bool doorDamaged = false;
	bool sfxToggle;
	float speed = 1.0f;
	int chosenHealth;
	int health;
	int score;
	int lastMovement;
	int looper;

	float lastMovementTime = 0.0f;
	float invulnerableTime = 0.0f;

	Mix_Chunk* hurtSFX = NULL;
	Mix_Chunk* particleSFX = NULL;

private:



};

#endif 