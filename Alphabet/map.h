#pragma once
#include <SDL.h>
#include <note.h>
#include <vector>
#include <timer.h>
struct Map
{
	std::vector<Note*> notes;
	int overallDifficulty;
	int approachRate;

	bool loadMap(SDL_Renderer* renderer, std::vector<Note*> notes) {
		this->notes = notes;
		for (Note* note : notes) {
			note->loadNote(renderer, note->hitTime, note->noteDuration);
		}
		return true;
	}

	void tick(SDL_Renderer* renderer, Timer* timer) {
		for (Note* note : notes) {
			note->tick(renderer, timer);
		}
	}

	void render(SDL_Renderer* renderer) {
		for (Note* note : notes) {
			note->render(renderer);
		}
	}
};