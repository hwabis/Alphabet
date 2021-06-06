#include "Note.h"

bool Note::loadNote(SDL_Renderer* renderer) {

	//100 to 2000 ish? check taiko's max AR
	scrollSpeed = 500.0f;

	bool success = true;

	noteTexture = Texture::loadTexture(NOTE_PATH, renderer);
	if (noteTexture == NULL)
	{
		printf("Failed to load note image!\n");
		success = false;
	}

	return success;
}

void Note::move(float timeStep) {
	pos->x -= scrollSpeed*timeStep;
	if (pos->x <= 0) {
		destroy();
	}
}

void Note::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, noteTexture, NULL, pos);
}

void Note::destroy() {
	SDL_DestroyTexture(noteTexture);
	noteTexture = NULL;
}