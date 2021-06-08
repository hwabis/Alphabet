#pragma once
#include <SDL.h>
class Timer
{
public:
	float getTimeStep() {
		return ((float)SDL_GetTicks() - tickTime);
	}
	void resetTickTime() {
		tickTime = (float)SDL_GetTicks();
	}
	float getTime() {
		return SDL_GetTicks() - startTime;
	}
	void resetStartTime() {
		startTime = (float)SDL_GetTicks();
	}
private:
	float startTime;
	float tickTime;
};