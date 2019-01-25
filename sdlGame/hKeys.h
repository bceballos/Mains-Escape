#ifndef gameKeys
#define gameKeys
#include <string>
#include "SDL.h"

class Keys
{
public:
	SDL_Keycode forward;
	SDL_Keycode backward;
	SDL_Keycode left;
	SDL_Keycode right;
	SDL_Keycode sprint;
	SDL_Keycode pause;
	SDL_Keycode fullscreen;
	SDL_Keycode enter;
	SDL_Keycode log;

	void load(std::string path);

private:

};

#endif