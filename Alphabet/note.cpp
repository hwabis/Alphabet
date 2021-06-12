#include "Note.h"

bool Note::loadNote(SDL_Renderer* renderer, float hitTime, int key, Keyboard* kb) {

	this->hitTime = hitTime;
	this->key = key;
	this->currentDim = 0;

	index = kb->getKeyIndex(key);
	feedbackArea->x = kb->key_positions[index].first;
	feedbackArea->y = kb->key_positions[index].second;
	//hard coded lol
	feedbackArea->h = 35; 
	feedbackArea->w = 104;

	bool success = true;

	noteTexture = Texture::loadTexture(NOTE_PATH, renderer);
	if (noteTexture == NULL)
	{
		printf("Failed to load note image!\n");
		success = false;
	}
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

void Note::tick(SDL_Renderer* renderer, Timer* timer, Keyboard* kb) {
	if (done) {
		if (feedbackTimer->getTime() < FEEDBACK_LENGTH) {
			renderFeedback(renderer, feedbackType);
		}
		else if (!feedbackDone) {
			freeFeedback();
			feedbackDone = true;
		}
	}
	else {
		if (!shown && timer->getTime() >= hitTime - noteDuration) {
			shown = true;
		}
		if (shown) {
			if (currentDim < RECT_MAX_DIM) {
				currentDim += timer->getTimeStep() * RECT_MAX_DIM / noteDuration;
			}
			renderNote(renderer, kb);

			if (getTimeFromHit(timer) >= missWindow) {
				//missed by delay
				feedbackType = 0;
				freeNote();
				done = true;
			}
		}
	}
}

void Note::renderNote(SDL_Renderer* renderer, Keyboard* kb) {
	index = kb->getKeyIndex(key);
	renderArea->x = kb->key_positions[index].first + RECT_MAX_DIM / 2 - currentDim / 2;
	renderArea->y = kb->key_positions[index].second + RECT_MAX_DIM / 2 - currentDim / 2;
	renderArea->h = currentDim;
	renderArea->w = currentDim;
	SDL_RenderCopy(renderer, noteTexture, NULL, renderArea);
}

void Note::handleInput(SDL_Renderer* renderer, Timer* timer, SDL_Event e) {
	if (!done && e.key.keysym.sym == key) {
		float timeDiff = abs(getTimeFromHit(timer));
		if (timeDiff <= perfWindow) {
			//perfect
			feedbackType = 2;
		}
		else if (timeDiff <= hitWindow) {
			//ok
			feedbackType = 1;
		}
		else {
			//miss
			feedbackType = 0;
		}
		freeNote();
		done = true;
	}
}

void Note::renderFeedback(SDL_Renderer* renderer, int type) {
	switch (type) {
	case 2:
		SDL_RenderCopy(renderer, perfTexture, NULL, feedbackArea);
		break;
	case 1:
		SDL_RenderCopy(renderer, okTexture, NULL, feedbackArea);
		break;
	case 0:
		SDL_RenderCopy(renderer, missTexture, NULL, feedbackArea);
		break;
	}
}

void Note::freeNote() {
	feedbackTimer->resetStartTime();
	SDL_DestroyTexture(noteTexture);
	noteTexture = NULL;
}

void Note::freeFeedback() {
	SDL_DestroyTexture(perfTexture);
	SDL_DestroyTexture(okTexture);
	SDL_DestroyTexture(missTexture);
	perfTexture = NULL;
	okTexture = NULL;
	missTexture = NULL;
}

float Note::getTimeFromHit(Timer* timer) {
	return timer->getTime() - hitTime;
}