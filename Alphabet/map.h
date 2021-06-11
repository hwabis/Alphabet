#pragma once
#include <SDL.h>
#include <note.h>
#include <vector>
#include <timer.h>
#include <keyboard.h>
struct Map
{
	std::vector<Note*> notes;
	int approachRate;

	bool loadMap(SDL_Renderer* renderer, std::vector<Note*> notes, float overallDifficulty);
	void tick(SDL_Renderer* renderer, Timer* timer, Keyboard* kb, std::vector<int>& keyQueue);
	void handleInput(SDL_Renderer* renderer, Timer* timer, SDL_Event e);

	float getDelay();
	void delayAllNotes(float delay);

	const std::string PERFECT_PATH = "res/sprites/perfect.png";
	const std::string OK_PATH = "res/sprites/ok.png";
	const std::string MISS_PATH = "res/sprites/miss.png";
	const float FEEDBACK_LENGTH = 300;

	SDL_Texture* perfTexture = NULL;
	SDL_Texture* okTexture = NULL;
	SDL_Texture* missTexture = NULL;

	Timer* feedbackTimer = new Timer();
	//constants not needed... 
	SDL_Rect* feedbackPos = new SDL_Rect{ 176, 330, 150, 50 };
	void renderFeedback(SDL_Renderer* renderer, int type);
	void hitNote();
	bool feedbackShown = false;

	//2 for perf, 1 for ok, 0 for miss, -1 for nothing
	int renderType;
};