#pragma once
#include <SDL.h>
#include <note.h>
#include <vector>
#include <timer.h>
#include <keyboard.h>
struct Map
{
	std::vector<Note*> notes;
	int overallDifficulty;
	int approachRate;

	bool loadMap(SDL_Renderer* renderer, std::vector<Note*> notes);
	void tick(SDL_Renderer* renderer, Timer* timer);
	void render(SDL_Renderer* renderer);
	void handleInput(SDL_Renderer* renderer, Timer* timer, SDL_Event e);

	float getDelay();
	void delayAllNotes(float delay);
};