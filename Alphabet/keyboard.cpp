#include "keyboard.h"

void Keyboard::initKeyboard() {
	validKeys[0] = SDLK_q;
	validKeys[1] = SDLK_w;
	validKeys[2] = SDLK_e;
	validKeys[3] = SDLK_r;
	validKeys[4] = SDLK_t;
	validKeys[4] = SDLK_y;
	validKeys[5] = SDLK_u;
	validKeys[6] = SDLK_i;
	validKeys[7] = SDLK_o;
	validKeys[8] = SDLK_p;
	validKeys[9] = SDLK_LEFTBRACKET;
	validKeys[10] = SDLK_RIGHTBRACKET;
	validKeys[11] = SDLK_a;
	validKeys[12] = SDLK_s;
	validKeys[13] = SDLK_d;
	validKeys[14] = SDLK_f;
	validKeys[15] = SDLK_g;
	validKeys[16] = SDLK_h;
	validKeys[17] = SDLK_j;
	validKeys[18] = SDLK_k;
	validKeys[19] = SDLK_l;
	validKeys[20] = SDLK_SEMICOLON;
	validKeys[21] = SDLK_QUOTE;
	validKeys[22] = SDLK_z;
	validKeys[23] = SDLK_x;
	validKeys[24] = SDLK_c;
	validKeys[25] = SDLK_v;
	validKeys[26] = SDLK_b;
	validKeys[27] = SDLK_n;
	validKeys[28] = SDLK_m;
	validKeys[29] = SDLK_COMMA;
	validKeys[30] = SDLK_PERIOD;
	validKeys[31] = SDLK_SLASH;
	validKeys[32] = SDLK_SPACE;

	for (int i = 0; i < 12; ++i)
		Keyboard::key_positions[i] = std::make_pair(9 + 113 * i, 270);
	for (int i = 12; i < 23; ++i)
		Keyboard::key_positions[i] = std::make_pair(37 + 113 * (i - 12), 383);
	for (int i = 23; i < 33; ++i)
		Keyboard::key_positions[i] = std::make_pair(95 + 113 * (i - 23), 496);
	Keyboard::key_positions[33] = std::make_pair(265, 609);
}

bool Keyboard::isValidKey(int sym) {
	for (int key : validKeys) {
		if (sym == key)
			return true;
	}
	return false;
}

void Keyboard::setKeyDownPos(SDL_Rect* keyDownPos, SDL_Event e) {
	switch (e.key.keysym.sym)
	{
	case SDLK_q:
		keyDownPos->x = key_positions[key_names::q].first;
		keyDownPos->y = key_positions[key_names::q].second;
		break;
	case SDLK_w:
		keyDownPos->x = key_positions[key_names::w].first;
		keyDownPos->y = key_positions[key_names::w].second;
		break;
	case SDLK_e:
		keyDownPos->x = key_positions[key_names::e].first;
		keyDownPos->y = key_positions[key_names::e].second;
		break;
	case SDLK_r:
		keyDownPos->x = key_positions[key_names::r].first;
		keyDownPos->y = key_positions[key_names::r].second;
		break;
	case SDLK_t:
		keyDownPos->x = key_positions[key_names::t].first;
		keyDownPos->y = key_positions[key_names::t].second;
		break;
	case SDLK_y:
		keyDownPos->x = key_positions[key_names::y].first;
		keyDownPos->y = key_positions[key_names::y].second;
		break;
	case SDLK_u:
		keyDownPos->x = key_positions[key_names::u].first;
		keyDownPos->y = key_positions[key_names::u].second;
		break;
	case SDLK_i:
		keyDownPos->x = key_positions[key_names::i].first;
		keyDownPos->y = key_positions[key_names::i].second;
		break;
	case SDLK_o:
		keyDownPos->x = key_positions[key_names::o].first;
		keyDownPos->y = key_positions[key_names::o].second;
		break;
	case SDLK_p:
		keyDownPos->x = key_positions[key_names::p].first;
		keyDownPos->y = key_positions[key_names::p].second;
		break;
	case SDLK_LEFTBRACKET:
		keyDownPos->x = key_positions[key_names::leftBracket].first;
		keyDownPos->y = key_positions[key_names::leftBracket].second;
		break;
	case SDLK_RIGHTBRACKET:
		keyDownPos->x = key_positions[key_names::rightBracket].first;
		keyDownPos->y = key_positions[key_names::rightBracket].second;
		break;
	case SDLK_a:
		keyDownPos->x = key_positions[key_names::a].first;
		keyDownPos->y = key_positions[key_names::a].second;
		break;
	case SDLK_s:
		keyDownPos->x = key_positions[key_names::s].first;
		keyDownPos->y = key_positions[key_names::s].second;
		break;
	case SDLK_d:
		keyDownPos->x = key_positions[key_names::d].first;
		keyDownPos->y = key_positions[key_names::d].second;
		break;
	case SDLK_f:
		keyDownPos->x = key_positions[key_names::f].first;
		keyDownPos->y = key_positions[key_names::f].second;
		break;
	case SDLK_g:
		keyDownPos->x = key_positions[key_names::g].first;
		keyDownPos->y = key_positions[key_names::g].second;
		break;
	case SDLK_h:
		keyDownPos->x = key_positions[key_names::h].first;
		keyDownPos->y = key_positions[key_names::h].second;
		break;
	case SDLK_j:
		keyDownPos->x = key_positions[key_names::j].first;
		keyDownPos->y = key_positions[key_names::j].second;
		break;
	case SDLK_k:
		keyDownPos->x = key_positions[key_names::k].first;
		keyDownPos->y = key_positions[key_names::k].second;
		break;
	case SDLK_l:
		keyDownPos->x = key_positions[key_names::l].first;
		keyDownPos->y = key_positions[key_names::l].second;
		break;
	case SDLK_SEMICOLON:
		keyDownPos->x = key_positions[key_names::semicolon].first;
		keyDownPos->y = key_positions[key_names::semicolon].second;
		break;
	case SDLK_QUOTE:
		keyDownPos->x = key_positions[key_names::quote].first;
		keyDownPos->y = key_positions[key_names::quote].second;
		break;
	case SDLK_z:
		keyDownPos->x = key_positions[key_names::z].first;
		keyDownPos->y = key_positions[key_names::z].second;
		break;
	case SDLK_x:
		keyDownPos->x = key_positions[key_names::x].first;
		keyDownPos->y = key_positions[key_names::x].second;
		break;
	case SDLK_c:
		keyDownPos->x = key_positions[key_names::c].first;
		keyDownPos->y = key_positions[key_names::c].second;
		break;
	case SDLK_v:
		keyDownPos->x = key_positions[key_names::v].first;
		keyDownPos->y = key_positions[key_names::v].second;
		break;
	case SDLK_b:
		keyDownPos->x = key_positions[key_names::b].first;
		keyDownPos->y = key_positions[key_names::b].second;
		break;
	case SDLK_n:
		keyDownPos->x = key_positions[key_names::n].first;
		keyDownPos->y = key_positions[key_names::n].second;
		break;
	case SDLK_m:
		keyDownPos->x = key_positions[key_names::m].first;
		keyDownPos->y = key_positions[key_names::m].second;
		break;
	case SDLK_COMMA:
		keyDownPos->x = key_positions[key_names::comma].first;
		keyDownPos->y = key_positions[key_names::comma].second;
		break;
	case SDLK_PERIOD:
		keyDownPos->x = key_positions[key_names::period].first;
		keyDownPos->y = key_positions[key_names::period].second;
		break;
	case SDLK_SLASH:
		keyDownPos->x = key_positions[key_names::slash].first;
		keyDownPos->y = key_positions[key_names::slash].second;
		break;
	case SDLK_SPACE:
		keyDownPos->x = key_positions[key_names::spacebar].first;
		keyDownPos->y = key_positions[key_names::spacebar].second;
		break;
	}
}

void Keyboard::destroy() {
	//Free loaded keyboard image
	SDL_DestroyTexture(gKeyboardTexture);
	gKeyboardTexture = NULL;

	//Free loaded keydown image
	SDL_DestroyTexture(gKeyDownTexture);
	gKeyDownTexture = NULL;
}