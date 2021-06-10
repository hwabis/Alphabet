#include "Map.h"

bool Map::loadMap(SDL_Renderer* renderer, std::vector<Note*> notes) {
	this->notes = notes;
	for (Note* note : notes) {
		note->loadNote(renderer, note->hitTime, note->noteDuration, note->key);
		// TODO: convert all these from OD instead of hard value
		note->missWindow = 200; 
		note->hitWindow = 100;
		note->perfWindow = 50;
	}
	return true;
}

void Map::tick(SDL_Renderer* renderer, Timer* timer) {
	for (Note* note : notes) {
		note->tick(renderer, timer);
	}
}

void Map::render(SDL_Renderer* renderer) {
	for (Note* note : notes) {
		note->render(renderer);
	}
}

void Map::handleInput(SDL_Renderer* renderer, Timer* timer, SDL_Event e) {
	for (Note* note : notes) {
		if (abs(timer->getTime() - note->hitTime) <= note->missWindow) {
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