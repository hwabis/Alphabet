#include "keyboard.h"

void Keyboard::initKeyboard() {
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
	validKeys[10] = SDLK_LEFTBRACKET;
	validKeys[11] = SDLK_RIGHTBRACKET;
	validKeys[12] = SDLK_a;
	validKeys[13] = SDLK_s;
	validKeys[14] = SDLK_d;
	validKeys[15] = SDLK_f;
	validKeys[16] = SDLK_g;
	validKeys[17] = SDLK_h;
	validKeys[18] = SDLK_j;
	validKeys[19] = SDLK_k;
	validKeys[20] = SDLK_l;
	validKeys[21] = SDLK_SEMICOLON;
	validKeys[22] = SDLK_QUOTE;
	validKeys[23] = SDLK_z;
	validKeys[24] = SDLK_x;
	validKeys[25] = SDLK_c;
	validKeys[26] = SDLK_v;
	validKeys[27] = SDLK_b;
	validKeys[28] = SDLK_n;
	validKeys[29] = SDLK_m;
	validKeys[30] = SDLK_COMMA;
	validKeys[31] = SDLK_PERIOD;
	validKeys[32] = SDLK_SLASH;
	validKeys[33] = SDLK_SPACE;

	for (int i = 0; i < 12; ++i)
		Keyboard::key_positions[i] = std::make_pair(9 + 113 * i, 270);
	for (int i = 12; i < 23; ++i)
		Keyboard::key_positions[i] = std::make_pair(37 + 113 * (i - 12), 383);
	for (int i = 23; i < 33; ++i)
		Keyboard::key_positions[i] = std::make_pair(95 + 113 * (i - 23), 496);
	Keyboard::key_positions[33] = std::make_pair(265, 609);
}

bool Keyboard::loadKeyboard(SDL_Renderer* renderer) {

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
	for (int i = 0; i < key_names::numberOfKeys; ++i) {
		//check it's not already being pressed
		if (e.key.keysym.sym == validKeys[i] && pressedKeys[i] == false) {
			pressedKeys[i] = true;

			SDL_Rect* keyDownPos = new SDL_Rect{ 0, 0, KEYDOWN_DIM, KEYDOWN_DIM };
			for (int j = 0; j < key_names::numberOfKeys; ++j) {
				if (e.key.keysym.sym == validKeys[j]) {
					keyDownPos->x = key_positions[j].first;
					keyDownPos->y = key_positions[j].second;
				}
			}
			SDL_RenderCopy(renderer, gKeyDownTexture, NULL, keyDownPos);
			Mix_PlayChannel(-1, onPressSound, 0);
		}
	}
}

void Keyboard::keyUp(SDL_Renderer* renderer, SDL_Event e) {
	SDL_RenderClear(renderer);
	for (int i = 0; i < key_names::numberOfKeys; ++i) {
		if (pressedKeys[i]) {
			if (e.key.keysym.sym == validKeys[i]) {
				//found the key we let go of
				pressedKeys[i] = false;
			}
			else {
				SDL_Rect* keyDownPos = new SDL_Rect{ 0, 0, KEYDOWN_DIM, KEYDOWN_DIM };
				keyDownPos->x = key_positions[i].first;
				keyDownPos->y = key_positions[i].second;
				SDL_RenderCopy(renderer, gKeyDownTexture, NULL, keyDownPos);
			}
		}
	}
}

void Keyboard::destroy() {
	//Free loaded keyboard image
	SDL_DestroyTexture(gKeyboardTexture);
	gKeyboardTexture = NULL;

	//Free loaded keydown image
	SDL_DestroyTexture(gKeyDownTexture);
	gKeyDownTexture = NULL;

	Mix_FreeChunk(onPressSound);
	onPressSound = NULL;
}