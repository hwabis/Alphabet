//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <utility>
#include <keyboard.h>
#include <music.h>
#include <background.h>
#include <note.h>
#include <map.h>
#include <timer.h>
#include <taikoConverter.h>
#include <score.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

Keyboard* kb = new Keyboard(); 
Music* music = new Music(); 
Background* bg = new Background(); 
Map* map = new Map(); 
Timer* timer = new Timer();
Score* score = new Score();

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Alphabet", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, 0xFF);

				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	kb->loadKeyboard(gRenderer);

	TaikoConverter* converter = new TaikoConverter(); 
	std::vector<Note*> notes = converter->makeNotes(gRenderer, "res/songs/Ray - Nagi (mingmichael) [Futsuu].osu", kb);

	music->loadMusic("res/songs/Nagi -nagi-.mp3");
	bg->loadBackground(gRenderer, "res/songs/nagi osu.jpg", 50);
	//any AR from 1 to 4 is good for beginners.
	//TODO: let user input AR, map path, bg path, music path
	map->loadMap(gRenderer, notes, converter->getOverallDifficulty("res/songs/Ray - Nagi (mingmichael) [Futsuu].osu"), 4, kb);

	//where's score? score is the only class that I actually wrote properly.. a constructor with parameters...
	//so it's already been "loaded" when it was initialized. lol.

	return true; //whatever.. this is too un-useful
}

void close()
{
	kb->free();
	music->free();
	bg->free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Event handler
			SDL_Event e;

			bool playingSong = false;
			float delay = map->getDelay();
			if (delay <= 0) {
				music->playSong();
				playingSong = true;
			}
			else {
				map->delayAllNotes(delay);
			}

			timer->resetStartTime();
			timer->resetTickTime(); 
			bool quit = false;
			//While application is running
			while (!quit)
			{
				if (!playingSong && timer->getTime() >= delay) {
					music->playSong();
					playingSong = true;
				}

				SDL_RenderClear(gRenderer);

				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					// when pressed down
					else if (e.type == SDL_KEYDOWN && kb->isValidKey(e.key.keysym.sym))
					{
						kb->keyDown(gRenderer, e);
						map->handleInput(gRenderer, timer, e, score);
					}
					else if (e.type == SDL_KEYUP)
					{
						kb->keyUp(gRenderer, e);
					}
				}

				bg->render(gRenderer);
				kb->render(gRenderer);

				map->tick(gRenderer, timer, kb, score);
				timer->resetTickTime();

				//Update screen
				SDL_RenderPresent(gRenderer);

				if (playingSong && !music->isPlaying()) {
					music->free();
					printf("RESULTS\n----------\nAccuracy: %.2f%%\nPerfect: %i\nOK: %i\nMiss: %i\n", 
						score->getAccuracy(), score->getCount(2), score->getCount(1), score->getCount(0));
					score->reset();
					break;
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}