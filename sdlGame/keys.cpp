#include "hKeys.h"
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

void Keys::load(std::string path) {
	std::ifstream inStream(path, std::ios::in);
	json jsonKeys;
	inStream >> jsonKeys;
	this->forward = SDL_GetKeyFromName(jsonKeys["forward"].get<std::string>().c_str());
	this->backward = SDL_GetKeyFromName(jsonKeys["backward"].get<std::string>().c_str());
	this->left = SDL_GetKeyFromName(jsonKeys["left"].get<std::string>().c_str());
	this->right = SDL_GetKeyFromName(jsonKeys["right"].get<std::string>().c_str());
	this->sprint = SDL_GetKeyFromName(jsonKeys["sprint"].get<std::string>().c_str());
	this->pause = SDL_GetKeyFromName(jsonKeys["pause"].get<std::string>().c_str());
	this->fullscreen = SDL_GetKeyFromName(jsonKeys["fullscreen"].get<std::string>().c_str());
	this->log = SDL_GetKeyFromName(jsonKeys["log"].get<std::string>().c_str());
	this->enter = SDL_GetKeyFromName(jsonKeys["enter"].get<std::string>().c_str());
	inStream.close();
}