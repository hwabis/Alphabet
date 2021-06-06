#pragma once
#include <SDL.h>
struct Timer
{
	float startTime;
	void restartTimer() {
		startTime = (float)SDL_GetTicks();
	}
	float getTimeStep() {
		return ((float)SDL_GetTicks() - startTime) / 1000.f;
	}
};