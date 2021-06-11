#pragma once
#include <SDL.h>
#include <note.h>
#include <vector>
#include <timer.h>
#include <keyboard.h>
struct Map
{
	std::vector<Note*> notes;
	int approachRate;

	bool loadMap(SDL_Renderer* renderer, std::vector<Note*> notes, float overallDifficulty, Keyboard* kb);
	void tick(SDL_Renderer* renderer, Timer* timer, Keyboard* kb);
	void handleInput(SDL_Renderer* renderer, Timer* timer, SDL_Event e);

	float getDelay();
	void delayAllNotes(float delay);
};