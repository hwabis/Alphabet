#include "background.h"

bool Background::loadBackground(SDL_Renderer* renderer, Uint8 alpha) {

	bool success = true;

	bgTexture = Texture::loadTexture(BG_PATH, renderer);

	SDL_SetTextureBlendMode(bgTexture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(bgTexture, alpha);

	if (bgTexture == NULL)
	{
		printf("Failed to load background image!\n");
		success = false;
	}

	return success;
}

SDL_Rect* Background::getArea() {
	int w, h;
	SDL_QueryTexture(bgTexture, NULL, NULL, &w, &h);
	//ugh hard code 1366 idk how to not do this
	return new SDL_Rect{ 1366/2 - w/2, 0, w, h };
}

void Background::destroy() {
	SDL_DestroyTexture(bgTexture);
	bgTexture = NULL;
}