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
	const float REACT_TIME = 400;

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

	//int return values are for Map to use
	bool loadNote(SDL_Renderer* renderer, float hitTime, float duration, int key);
	int tick(SDL_Renderer* renderer, Timer* timer, Keyboard* keyboard);
	void renderNote(SDL_Renderer* renderer);
	int handleInput(SDL_Renderer* renderer, Timer* timer, SDL_Event e);
	void free();

	float getTimeFromHit(Timer* timer);

	float xPos;
	SDL_Rect* pos = new SDL_Rect{ (int)xPos, 50, NOTE_WIDTH, NOTE_HEIGHT };

	std::string KEY_PATH = "res/sprites/keydownOrange.png";
	SDL_Texture* keyTexture = NULL;
	void renderKey(SDL_Renderer* renderer, int key, Keyboard* kb);
};