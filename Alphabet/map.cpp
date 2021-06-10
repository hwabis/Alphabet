#include "Map.h"

bool Map::loadMap(SDL_Renderer* renderer, std::vector<Note*> notes) {
	this->notes = notes;
	for (Note* note : notes) {
		note->loadNote(renderer, note->hitTime, note->noteDuration, note->key);
		// TODO: convert all these from OD instead of hard value
		note->missWindow = 200; 
		note->hitWindow = 150;
		note->perfWindow = 50;
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

void Map::tick(SDL_Renderer* renderer, Timer* timer) {
	for (Note* note : notes) {
		if (note->tick(renderer, timer) == 0) {
			//missed by delay
			renderType = 0;

			feedbackShown = true;
			feedbackTimer->resetStartTime();
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

void Map::handleInput(SDL_Renderer* renderer, Timer* timer, SDL_Event e) {
	for (Note* note : notes) {
		if (abs(note->getTimeFromHit(timer)) <= note->missWindow) {
			renderType = note->handleInput(renderer, timer, e);

			feedbackShown = true;
			feedbackTimer->resetStartTime();
			renderFeedback(renderer, renderType);

			break;
		}
	}
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