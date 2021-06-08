#include "Note.h"

bool Note::loadNote(SDL_Renderer* renderer, float hitTime, float duration) {

	this->xPos = SPAWN_LOC;
	this->hitTime = hitTime;
	this->noteDuration = duration;

	bool success = true;

	noteTexture = Texture::loadTexture(NOTE_PATH, renderer);
	if (noteTexture == NULL)
	{
		printf("Failed to load note image!\n");
		success = false;
	}

	return success;
}

void Note::tick(SDL_Renderer* renderer, Timer* timer) {
	if (!shown && timer->getTime() >= hitTime - (1 - HIT_AT_X / SPAWN_LOC) * noteDuration) {
		shown = true;
	}
	if (shown) {
		xPos -= SPAWN_LOC*timer->getTimeStep() / noteDuration;
		pos->x = xPos;
		render(renderer);
		if (xPos + NOTE_WIDTH <= 0) {
			free();
		}
	}
}

void Note::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, noteTexture, NULL, pos);
}

void Note::free() {
	SDL_DestroyTexture(noteTexture);
	noteTexture = NULL;
}