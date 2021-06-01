#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

struct Music
{
	const char* MUSIC_PATH = "res/songs/nagi.mp3";

	Mix_Music* song = NULL;

	bool loadMusic();
	void playSong();
	void destroy();
};