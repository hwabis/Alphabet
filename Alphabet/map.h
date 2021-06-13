#pragma once
#include <SDL.h>
#include <note.h>
#include <vector>
#include <timer.h>
#include <keyboard.h>
#include <score.h>
struct Map
{
	std::vector<Note*> notes;

	bool loadMap(SDL_Renderer* renderer, std::vector<Note*> notes, float overallDifficulty, float approachRate, Keyboard* kb);
	void tick(SDL_Renderer* renderer, Timer* timer, Keyboard* kb, Score* score);
	void handleInput(SDL_Renderer* renderer, Timer* timer, SDL_Event e, Score* score);

	float getDelay();
	void delayAllNotes(float delay);
};