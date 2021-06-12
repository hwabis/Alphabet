#include "Map.h"

bool Map::loadMap(SDL_Renderer* renderer, std::vector<Note*> notes, float overallDifficulty, Keyboard* kb) {
	this->notes = notes;
	for (Note* note : notes) {
		note->loadNote(renderer, note->hitTime, note->key, kb);
		//windows from https://osu.ppy.sh/wiki/en/Beatmapping/Overall_difficulty
		//divide by two because we check with time differences, not whether it's in the window
		note->missWindow = (400 - 20*overallDifficulty) / 2; //OD5: 300
		note->hitWindow = (280 - 16*overallDifficulty) / 2; //OD5: 200
		note->perfWindow = (160 - 12*overallDifficulty) / 2; //OD5: 100
	}

	return true; //meh
}

void Map::tick(SDL_Renderer* renderer, Timer* timer, Keyboard* kb) {
	for (Note* note : notes) {
		note->tick(renderer, timer, kb);
	}
}

void Map::handleInput(SDL_Renderer* renderer, Timer* timer, SDL_Event e) {
	for (Note* note : notes) {
		if (note->getTimeFromHit(timer) >= -note->missWindow && !note->done) {
			note->handleInput(renderer, timer, e);
			break;
		}
	}
}

float Map::getDelay() {
	for (Note* note : notes) {
		if (note->hitTime < note->noteDuration) {
			return note->noteDuration - note->hitTime;
			break;
		}
	}
	return 0;
}

void Map::delayAllNotes(float delay) {
	for (Note* note : notes) {
		note->hitTime += delay;
	}
}