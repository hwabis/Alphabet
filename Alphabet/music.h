#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

struct Music
{
	Mix_Music* song = NULL;

	bool loadMusic(std::string path);
	void playSong();
	void free();
};