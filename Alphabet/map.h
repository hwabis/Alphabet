#pragma once
#include <SDL.h>
#include <note.h>
#include <vector>
struct Map
{
	std::vector<Note*> notes;
	int overallDifficulty;
	int approachRate;

	bool loadMap(SDL_Renderer* renderer, std::vector<Note*> notes) {
		this->notes = notes;
		for (Note* note : notes) {
			note->loadNote(renderer);
		}
		return true;
	}

	void tick(float timeStep) {
		for (Note* note : notes) {
			note->move(timeStep);
		}
	}

	void render(SDL_Renderer* renderer) {
		for (Note* note : notes) {
			note->render(renderer);
		}
	}
};