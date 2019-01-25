#ifndef gameText
#define gameText

#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

class Font {

public:

	Font();
	~Font();

	SDL_Rect rect;
	TTF_Font* font;
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Color color;

	void init(std::string path, int size, int r, int g, int b, int x, int y, int w);
	void init(std::string path, int size, int r, int g, int b, int x, int y, int w, int h);
	void clearText();
	void setColor(int r, int g, int b);
	void render(SDL_Renderer* renderer, std::string text);

private:


};

#endif 
