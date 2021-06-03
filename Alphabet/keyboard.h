#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <utility>
#include <string>
#include <texture.h>

struct Keyboard
{
	const std::string KEYBOARD_PATH = "res/sprites/kb.png";
	const std::string KEYDOWN_PATH = "res/sprites/keydown.png";
	const char* PRESS_SOUND_PATH = "res/sounds/press.wav";

	const int KEYDOWN_DIM = 104;

	SDL_Texture* gKeyboardTexture = NULL;
	SDL_Texture* gKeyDownTexture = NULL;

	Mix_Chunk* onPressSound = NULL;

	enum key_names {
		//is this really needed
		q, w, e, r, t, y, u, i, o, p, leftBracket, rightBracket,
		a, s, d, f, g, h, j, k, l, semicolon, quote,
		z, x, c, v, b, n, m, comma, period, slash,
		numberOfKeys
	};
	int validKeys[key_names::numberOfKeys];
	std::pair<int, int> key_positions[numberOfKeys];
	bool pressedKeys[key_names::numberOfKeys];

	void initKeyboard();
	bool loadKeyboard(SDL_Renderer* renderer);
	bool isValidKey(int sym);
	void keyDown(SDL_Renderer* renderer, SDL_Event e);
	void keyUp(SDL_Renderer* renderer, SDL_Event e);
	void destroy();
};