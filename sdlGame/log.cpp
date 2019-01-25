#include "hLog.h"

Logging::Logging()
{
	log = true;

	std::fstream logFile("logs/logfile.log", std::fstream::out);
	logFile.close();
}

Logging::~Logging()
{
	
}

void Logging::logInit(std::string type, std::string objInit, float timeTaken) {
	if (log) {
		std::fstream logFile("logs/logfile.log", std::fstream::out | std::fstream::app);
		if (logFile.good()) {
			std::string logString = "[ " + realTime.returnDate() + " ][ " + realTime.returnTime() + " ] [ " + type + " ] time taken to " + objInit + " : " + std::to_string(timeTaken) + "ms";
			logFile << logString << std::endl;
			logFile.close();
		}
		else {
			std::cout << "File shite \n";
		}
	}
}

void Logging::logPositioning(SDL_Rect rect, std::string type) {
	if (log) {
		std::fstream logFile("logs/logfile.log", std::fstream::out | std::fstream::app);
		if (logFile.good()) {
			std::string logString = "[ " + realTime.returnDate() + " ][ " + realTime.returnTime() + " ] [ GAMEOBJECT POSITION ] the position of the " + type + " : " + std::to_string(rect.x) + ", " + std::to_string(rect.y) + " ";
			logFile << logString << std::endl;
			logFile.close();
		}
		else {
			std::cout << "File shite \n";
		}
	}
}

void Logging::logPerformance(float fps) {
	if (log) {
		std::fstream logFile("logs/logfile.log", std::fstream::out | std::fstream::app);
		if (logFile.good()) {
			std::string logString = "[ " + realTime.returnDate() + " ][ " + realTime.returnTime() + " ] FPS: " + std::to_string((int)ceil(1000 / fps)) + " Optimal FPS: 60";
			logFile << logString << std::endl;
			logFile.close();
		}
		else {
			std::cout << "File shite \n";
		}
	}
}

void Logging::logCollision(std::string message) {
	if (log) {
		std::fstream logFile("logs/logfile.log", std::fstream::out | std::fstream::app);
		if (logFile.good()) {
			std::string logString = "[ " + realTime.returnDate() + " ][ " + realTime.returnTime() + " ] [ COLLISION ] " + message;
			logFile << logString << std::endl;
			logFile.close();
		}
		else {
			std::cout << "File shite \n";
		}
	}
}

void Logging::logGeneral(std::string message) {
	if (log) {
		std::fstream logFile("logs/logfile.log", std::fstream::out | std::fstream::app);
		if (logFile.good()) {
			std::string logString = "[ " + realTime.returnDate() + " ][ " + realTime.returnTime() + " ] [ GENERAL ] " + message;
			logFile << logString << std::endl;
			logFile.close();
		}
		else {
			std::cout << "File shite \n";
		}
	}
}

void Logging::logRenderTime(float timeTaken) {
	if (log) {
		std::fstream logFile("logs/logfile.log", std::fstream::out | std::fstream::app);
		if (logFile.good()) {
			std::string logString = "[ " + realTime.returnDate() + " ][ " + realTime.returnTime() + " ] [ RENDER CYCLE TIME ] cycle number: " + std::to_string(renderCycles) + " time taken: " + std::to_string(timeTaken) + "ms average time: " + std::to_string(totalRenderTime / renderCycles) + "ms total time rendering: " + std::to_string(totalRenderTime) + "ms";
			totalRenderTime += timeTaken;
			renderCycles++;
			logFile << logString << std::endl;
			logFile.close();
		}
		else {
			std::cout << "File shite \n";
		}
	}
}

void Logging::logInput(std::string eventType, int timestamp, int keycode) {
	if (log) {
		std::fstream logFile("logs/logfile.log", std::fstream::out | std::fstream::app);
		if (logFile.good()) {
			std::string logString = "[ " + realTime.returnDate() + " ][ " + realTime.returnTime() + " ] [" + eventType + "] time: " + std::to_string(timestamp) + " code: " + std::to_string(keycode) + " key pressed: " + SDL_GetKeyName(keycode);
			logFile << logString << std::endl;
			logFile.close();
		}
		else {
			std::cout << "File shite \n";
		}
	}
}

void Logging::logTexture(std::string path, std::string objectName) {
	if (log) {
		std::fstream logFile("logs/logfile.log", std::fstream::out | std::fstream::app);
		if (logFile.good()) {
			std::string logString = "[ " + realTime.returnDate() + " ][ " + realTime.returnTime() + " ] [ TEXTURE LOADING ] texture at " + path + " loaded for " + objectName;
			logFile << logString << std::endl;
			logFile.close();
		}
		else {
			std::cout << "File shite \n";
		}
	}
}