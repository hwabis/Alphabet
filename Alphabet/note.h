#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <texture.h>
#include <timer.h>
#include <keyboard.h>
struct Note
{
	std::string NOTE_PATH = "res/sprites/bar.png";
	const int NOTE_HEIGHT = 260;
	const int NOTE_WIDTH = 18;
	const float HIT_AT_X = 240;
	const float SPAWN_LOC = 1366;

	bool shown = false;
	bool done = false;
	bool missed = false;

	//everything is in milliseconds
	float hitTime;
	//windows defined by Map
	float hitWindow;
	float perfWindow;
	float missWindow;

	float noteDuration; 
	int key; 

	SDL_Texture* noteTexture = NULL;

	bool loadNote(SDL_Renderer* renderer, float hitTime, float duration, int key);
	void tick(SDL_Renderer* renderer, Timer* timer);
	void render(SDL_Renderer* renderer);
	void handleInput(SDL_Renderer* renderer, Timer* timer, SDL_Event e);
	void free();

	float getTimeFromHit(Timer* timer);

	float xPos;
	SDL_Rect* pos = new SDL_Rect{ (int)xPos, 50, NOTE_WIDTH, NOTE_HEIGHT };
};