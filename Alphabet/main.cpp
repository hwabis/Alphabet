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
#include <keyQueue.h>

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

Keyboard* kb = new Keyboard(); //has path but it's fine
Music* music = new Music(); //has path but needs to be changeable
Background* bg = new Background(); //has path but needs to be changeable
Map* map = new Map(); //has path but it's fine
Timer* timer = new Timer();
KeyQueue* keyQ = new KeyQueue();

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
	bool loadKeyboard = kb->loadKeyboard(gRenderer);

	TaikoConverter* converter = new TaikoConverter(); 
	//this is how I want the path stuff to look like...
	std::vector<Note*> notes = converter->makeNotes(gRenderer, "res/songs/Ray - Nagi (mingmichael) [Futsuu].osu", kb, 3000);

	bool loadEverythingElse = music->loadMusic()
		&& bg->loadBackground(gRenderer, bg->alpha)
		&& map->loadMap(gRenderer, notes, converter->getOverallDifficulty("res/songs/Ray - Nagi (mingmichael) [Futsuu].osu"));

	return loadKeyboard && loadEverythingElse;
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
			timer->resetTickTime(); //TODO: implement note offset...
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
						map->handleInput(gRenderer, timer, e, keyQ->queue);
					}
					else if (e.type == SDL_KEYUP)
					{
						kb->keyUp(gRenderer, e);
					}
				}

				bg->render(gRenderer);
				kb->render(gRenderer);

				map->tick(gRenderer, timer, kb, keyQ->queue);
				timer->resetTickTime();

				for (int i = 0; i < keyQ->queue.size(); ++i) {
					printf("%i ", keyQ->queue[i]);
				}
				printf("\n");

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}