#pragma once
#include <SDL.h>
#include <string>
#include <texture.h>
struct Background
{
	const char* BG_PATH = "res/songs/nagi osu.jpg";
	Uint8 alpha = 50; //out of 255

	SDL_Texture* bgTexture = NULL;
	bool loadBackground(SDL_Renderer* renderer, Uint8 alpha);
	SDL_Rect* getArea();
	void render(SDL_Renderer* renderer);
	void destroy();
};