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

//Screen dimension constants
static const int SCREEN_WIDTH = 1366;
static const int SCREEN_HEIGHT = 768;

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
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
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
	kb->initKeyboard();

	return success;
}

bool loadMedia()
{
	return (kb->loadKeyboard(gRenderer) && music->loadMusic() && bg->loadBackground(gRenderer, bg->alpha));
}

void close()
{
	kb->destroy();
	music->destroy();
	bg->destroy();

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
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//render non changing stuff
			//Render keyboard texture to screen
			//TODO: make this all one method...?
			SDL_RenderCopy(gRenderer, bg->bgTexture, NULL, bg->getArea());
			SDL_RenderCopy(gRenderer, kb->gKeyboardTexture, NULL, NULL);
			music->playSong();

			//render changing stuff
			//While application is running
			while (!quit)
			{
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
					}
					else if (e.type == SDL_KEYUP)
					{
						kb->keyUp(gRenderer, e);
						SDL_RenderCopy(gRenderer, bg->bgTexture, NULL, bg->getArea());
						SDL_RenderCopy(gRenderer, kb->gKeyboardTexture, NULL, NULL);
					}
				}

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}