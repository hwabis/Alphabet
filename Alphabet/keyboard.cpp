#include "keyboard.h"

bool Keyboard::loadKeyboard(SDL_Renderer* renderer) {
	validKeys[0] = SDLK_q;
	validKeys[1] = SDLK_w;
	validKeys[2] = SDLK_e;
	validKeys[3] = SDLK_r;
	validKeys[4] = SDLK_t;
	validKeys[5] = SDLK_y;
	validKeys[6] = SDLK_u;
	validKeys[7] = SDLK_i;
	validKeys[8] = SDLK_o;
	validKeys[9] = SDLK_p;
	validKeys[10] = SDLK_a;
	validKeys[11] = SDLK_s;
	validKeys[12] = SDLK_d;
	validKeys[13] = SDLK_f;
	validKeys[14] = SDLK_g;
	validKeys[15] = SDLK_h;
	validKeys[16] = SDLK_j;
	validKeys[17] = SDLK_k;
	validKeys[18] = SDLK_l;
	validKeys[19] = SDLK_SEMICOLON;
	validKeys[20] = SDLK_z;
	validKeys[21] = SDLK_x;
	validKeys[22] = SDLK_c;
	validKeys[23] = SDLK_v;
	validKeys[24] = SDLK_b;
	validKeys[25] = SDLK_n;
	validKeys[26] = SDLK_m;
	validKeys[27] = SDLK_COMMA;
	validKeys[28] = SDLK_PERIOD;
	validKeys[29] = SDLK_SLASH;

	for (int i = 0; i < 10; ++i)
		key_positions[i] = std::make_pair(9 + 113 * i, 416);
	for (int i = 10; i < 20; ++i)
		key_positions[i] = std::make_pair(37 + 113 * (i - 10), 529);
	for (int i = 20; i < 30; ++i)
		key_positions[i] = std::make_pair(95 + 113 * (i - 20), 642);

	bool success = true;

	//Load keyboard texture
	gKeyboardTexture = Texture::loadTexture(KEYBOARD_PATH, renderer);
	if (gKeyboardTexture == NULL)
	{
		printf("Failed to load keyboard image!\n");
		success = false;
	}

	//Load keyDown texture
	gKeyDownTexture = Texture::loadTexture(KEYDOWN_PATH, renderer);
	if (gKeyDownTexture == NULL)
	{
		printf("Failed to load keydown image!\n");
		success = false;
	}

	//Load sound effects
	onPressSound = Mix_LoadWAV(PRESS_SOUND_PATH);
	if (onPressSound == NULL)
	{
		printf("Failed to load press sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}

bool Keyboard::isValidKey(int sym) {
	for (int key : validKeys) {
		if (sym == key)
			return true;
	}
	return false;
}

void Keyboard::keyDown(SDL_Renderer* renderer, SDL_Event e) {
	for (int i = 0; i < numberOfKeys; ++i) {
		//check it's not already being pressed
		if (e.key.keysym.sym == validKeys[i] && pressedKeys[i] == false) {
			pressedKeys[i] = true;
			Mix_PlayChannel(-1, onPressSound, 0);
		}
	}
}

void Keyboard::keyUp(SDL_Renderer* renderer, SDL_Event e) {
	for (int i = 0; i < numberOfKeys; ++i) {
		if (pressedKeys[i] && e.key.keysym.sym == validKeys[i]) {
			pressedKeys[i] = false;
		}
	}
}

void Keyboard::render(SDL_Renderer* renderer) {
	for (int i = 0; i < numberOfKeys; ++i) {
		if (pressedKeys[i]) {
			//is this bad lol.. run out of memory?
			SDL_Rect* keyDownPos = new SDL_Rect{ 0, 0, KEYDOWN_DIM, KEYDOWN_DIM };
			keyDownPos->x = key_positions[i].first;
			keyDownPos->y = key_positions[i].second;
			SDL_RenderCopy(renderer, gKeyDownTexture, NULL, keyDownPos);
		}
	}
	SDL_RenderCopy(renderer, gKeyboardTexture, NULL, NULL);
}

void Keyboard::free() {
	//Free loaded keyboard image
	SDL_DestroyTexture(gKeyboardTexture);
	gKeyboardTexture = NULL;

	//Free loaded keydown image
	SDL_DestroyTexture(gKeyDownTexture);
	gKeyDownTexture = NULL;

	Mix_FreeChunk(onPressSound);
	onPressSound = NULL;
}