#include <iostream>
#include "hFont.h"

void Font::init(std::string path, int size, int r, int g, int b, int x, int y, int w) {
	font = TTF_OpenFont(path.c_str(), size);

	color = SDL_Color{ (uint8_t)r, (uint8_t)g, (uint8_t)b };
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = size + 5;
}

void Font::init(std::string path, int size, int r, int g, int b, int x, int y, int w, int h) {
	font = TTF_OpenFont(path.c_str(), size);

	color = SDL_Color{ (uint8_t)r, (uint8_t)g, (uint8_t)b };
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

void Font::render(SDL_Renderer* renderer, std::string text) {
	clearText();

	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Font::setColor(int r, int g, int b) {
	color = SDL_Color{ (uint8_t)r, (uint8_t)g, (uint8_t)b };
}

void Font::clearText() {
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

Font::~Font() {
	clearText();
	TTF_CloseFont(font);
}

Font::Font() {

}