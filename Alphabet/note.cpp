#include "Note.h"

bool Note::loadNote(SDL_Renderer* renderer, float hitTime, float duration, int key) {

	this->xPos = SPAWN_LOC;
	this->hitTime = hitTime;
	this->noteDuration = duration;
	this->key = key;

	bool success = true;

	noteTexture = Texture::loadTexture(NOTE_PATH, renderer);
	if (noteTexture == NULL)
	{
		printf("Failed to load note image!\n");
		success = false;
	}

	return success;
}

int Note::tick(SDL_Renderer* renderer, Timer* timer, Keyboard* kb) {
	if (!shown && !done && timer->getTime() >= hitTime - (1 - HIT_AT_X / SPAWN_LOC) * noteDuration) {
		shown = true;
	}
	if (shown) {
		xPos -= SPAWN_LOC*timer->getTimeStep() / noteDuration;
		pos->x = xPos;
		renderNote(renderer);

		if (!done && !missed && getTimeFromHit(timer) >= missWindow) {
			//missed by delay
			missed = true;
			return 0;
		}

		if (xPos + NOTE_WIDTH <= 0) {
			//reached end of screen
			free();
		}
	}
	return -1;
}

void Note::renderNote(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, noteTexture, NULL, pos);
}

/*void Note::renderKey(SDL_Renderer* renderer, int key, Keyboard* kb) {
	int index = 0;
	for (int i = 0; i < kb->numberOfKeys; ++i) {
		if (kb->validKeys[i] == key) {
			index = i;
			break;
		}
	}
	//UHH these 104's should come from Keyboard::KEYDOWN_DIM
	SDL_Rect* pos = new SDL_Rect{ kb->key_positions[index].first, kb->key_positions[index].second, 104, 104 }; 
	SDL_RenderCopy(renderer, keyTexture, NULL, pos);
}*/

int Note::handleInput(SDL_Renderer* renderer, Timer* timer, SDL_Event e) {
	int retval = -1;
	if (!done && e.key.keysym.sym == key) {
		float timeDiff = abs(getTimeFromHit(timer));
		if (timeDiff <= perfWindow) {
			//perfect
			retval = 2;
		}
		else if (timeDiff <= hitWindow) {
			//ok
			retval = 1;
		}
		else {
			//miss
			retval = 0;
		}
		free();
		done = true;
	}
	return retval;
}

void Note::free() {
	SDL_DestroyTexture(noteTexture);
	noteTexture = NULL;
}

float Note::getTimeFromHit(Timer* timer) {
	return timer->getTime() - hitTime;
}