#pragma once
#include <SDL.h>
#include <utility>

struct Keyboard
{
	SDL_Texture* gKeyboardTexture = NULL;
	SDL_Texture* gKeyDownTexture = NULL;
	enum key_names {
		q, w, e, r, t, y, u, i, o, p, leftBracket, rightBracket,
		a, s, d, f, g, h, j, k, l, semicolon, quote,
		z, x, c, v, b, n, m, comma, period, slash,
		spacebar, numberOfKeys
	};
	int validKeys[key_names::numberOfKeys];
	std::pair<int, int> key_positions[numberOfKeys];

	void initKeyboard();
	bool isValidKey(int sym);
	void setKeyDownPos(SDL_Rect* keyDownPos, SDL_Event e);
	void destroy();
};