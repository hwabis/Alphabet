#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <texture.h>
struct Note
{
	std::string NOTE_PATH = "res/sprites/bar.png";
	int NOTE_HEIGHT = 260;
	int NOTE_WIDTH = 18;
	int HIT_AT = 240;

	float hitTime;
	float hitWindow;
	float scrollSpeed;
	int key; //will get from Keyboard::key_names

	SDL_Texture* noteTexture = NULL;

	bool loadNote(SDL_Renderer* renderer);
	void move(float timeStep);
	void render(SDL_Renderer* renderer);
	void destroy();

	SDL_Rect* pos = new SDL_Rect{ 1350, 50, NOTE_WIDTH, NOTE_HEIGHT };
};