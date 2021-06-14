#pragma once
#include <SDL.h>
#include <keyboard.h>
#include <vector>
#include <note.h>
#include <fStream>

struct TaikoConverter
{
	//why not make a standard converter?
	//I think taiko is more appropriate for this gamemode since
	//taiko maps only focus on rhythm, whereas std maps often 
	//dumb-down their rhythm in return for spacing patterns...
	std::vector<Note*> makeNotes(SDL_Renderer* renderer, std::string path, Keyboard* kb);

	float getOverallDifficulty(std::string path);

	std::string getSongPath(std::string path);
	std::string getBackgroundPath(std::string path);
};