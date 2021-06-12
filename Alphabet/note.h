#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <texture.h>
#include <timer.h>
#include <keyboard.h>
#include <vector>
struct Note
{
	std::string NOTE_PATH = "res/sprites/approachRect.png";
	const int RECT_MAX_DIM = 104;
	
	float currentDim;

	bool shown = false;
	bool done = false;

	//everything is in milliseconds
	float hitTime;
	//windows and noteDuration defined by Map
	//(OD and AR respectively)
	float hitWindow;
	float perfWindow;
	float missWindow;
	float noteDuration; 

	int key; 

	SDL_Texture* noteTexture = NULL;

	bool loadNote(SDL_Renderer* renderer, float hitTime, int key, Keyboard* kb);
	void tick(SDL_Renderer* renderer, Timer* timer, Keyboard* kb);
	void renderNote(SDL_Renderer* renderer, Keyboard* kb);
	void handleInput(SDL_Renderer* renderer, Timer* timer, SDL_Event e);
	void freeNote();

	SDL_Rect* renderArea = new SDL_Rect{};
	//i think now i get why you initialize stuff here... so your memory doesn't explode...
	int index;

	float getTimeFromHit(Timer* timer);

	SDL_Texture* perfTexture = NULL;
	SDL_Texture* okTexture = NULL;
	SDL_Texture* missTexture = NULL;
	const std::string PERFECT_PATH = "res/sprites/perfect.png";
	const std::string OK_PATH = "res/sprites/ok.png";
	const std::string MISS_PATH = "res/sprites/miss.png";
	const float FEEDBACK_LENGTH = 200;
	//2 = perfect, 1 = ok, 0 = miss
	int feedbackType;
	void renderFeedback(SDL_Renderer* renderer, int type);
	SDL_Rect* feedbackArea = new SDL_Rect{}; 
	void freeFeedback();
	Timer* feedbackTimer = new Timer();
	bool feedbackDone = false;
};