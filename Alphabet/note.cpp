#include "Note.h"

bool Note::loadNote(SDL_Renderer* renderer) {

	scrollSpeed = 10;

	bool success = true;

	//Load keyboard texture
	noteTexture = Texture::loadTexture(NOTE_PATH, renderer);
	if (noteTexture == NULL)
	{
		printf("Failed to load note image!\n");
		success = false;
	}

	return success;
}

void Note::move(Uint32 timeStep) {
	pos->x -= scrollSpeed;
}


void Note::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, noteTexture, NULL, pos);
}