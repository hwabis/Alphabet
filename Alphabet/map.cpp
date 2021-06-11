#include "Map.h"

bool Map::loadMap(SDL_Renderer* renderer, std::vector<Note*> notes, float overallDifficulty) {
	this->notes = notes;
	for (Note* note : notes) {
		note->loadNote(renderer, note->hitTime, note->noteDuration, note->key);
		//windows from https://osu.ppy.sh/wiki/en/Beatmapping/Overall_difficulty
		note->missWindow = 400 - 20*overallDifficulty; 
		note->hitWindow = 280 - 16*overallDifficulty;
		note->perfWindow = 160 - 12*overallDifficulty;
	}

	feedbackTimer->resetStartTime();
	feedbackTimer->resetTickTime();

	bool success = true;
	perfTexture = Texture::loadTexture(PERFECT_PATH, renderer);
	if (perfTexture == NULL)
	{
		printf("Failed to load perfTexture!\n");
		success = false;
	}
	okTexture = Texture::loadTexture(OK_PATH, renderer);
	if (okTexture == NULL)
	{
		printf("Failed to load okTexture!\n");
		success = false;
	}
	missTexture = Texture::loadTexture(MISS_PATH, renderer);
	if (missTexture == NULL)
	{
		printf("Failed to load missTexture!\n");
		success = false;
	} //lol i keep copy pasting this...
	return success;
}

void Map::tick(SDL_Renderer* renderer, Timer* timer, Keyboard* kb, std::vector<int>& keyQueue) {
	for (Note* note : notes) {
		if (note->tick(renderer, timer, kb, keyQueue) == 0) {
			//missed by delay
			renderType = 0;
			hitNote();
			renderFeedback(renderer, renderType);
		}
	}
	if (feedbackShown) {
		if (feedbackTimer->getTime() < FEEDBACK_LENGTH) {
			renderFeedback(renderer, renderType);
		}
		else {
			feedbackShown = false;
		}
	}
}

void Map::handleInput(SDL_Renderer* renderer, Timer* timer, SDL_Event e, std::vector<int>& keyQueue) {
	for (Note* note : notes) {
		if (abs(note->getTimeFromHit(timer)) <= note->missWindow) {
			renderType = note->handleInput(renderer, timer, e, keyQueue);
			hitNote();
			renderFeedback(renderer, renderType);
			break;
		}
	}
}

void Map::hitNote() {
	feedbackShown = true;
	feedbackTimer->resetStartTime();
}

void Map::renderFeedback(SDL_Renderer* renderer, int type) {
	switch (type) {
	case 2:
		SDL_RenderCopy(renderer, perfTexture, NULL, feedbackPos);
		break;
	case 1:
		SDL_RenderCopy(renderer, okTexture, NULL, feedbackPos);
		break;
	case 0:
		SDL_RenderCopy(renderer, missTexture, NULL, feedbackPos);
		break;
	case -1:
		break;
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