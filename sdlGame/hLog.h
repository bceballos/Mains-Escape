#ifndef gameLogger
#define gameLogger

#include <iostream>
#include <fstream>
#include <string>
#include "hTimer.h"
#include "SDL.h"

class Logging
{
public:

	// 1000/ (SDL_GetTicks() -  timer.getTicks())
	Timer realTime;

	bool log = true;

	void logGeneral(std::string message);
	void logInput(std::string eventType, int timestamp, int keycode);
	void logRenderTime(float timeTaken);
	void logInit(std::string type, std::string objInit, float timeTaken);
	void logPerformance(float fps);
	void logPositioning(SDL_Rect rect, std::string type);
	void logCollision(std::string message);
	void logTexture(std::string path, std::string objectName);

	long renderCycles = 0;
	long fpsCycles = 0;
	double totalRenderTime = 0.0f;
	double averageFPS = 0.0f;

	Logging();
	~Logging();

private:

};

#endif
