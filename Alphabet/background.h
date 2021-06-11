#pragma once
#include <SDL.h>
#include <string>
#include <texture.h>
struct Background
{
	SDL_Texture* bgTexture = NULL;
	bool loadBackground(SDL_Renderer* renderer, std::string path, Uint8 alpha);
	SDL_Rect* getArea();
	void render(SDL_Renderer* renderer);
	void free();
};