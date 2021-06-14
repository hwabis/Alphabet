//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <iostream>
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
TaikoConverter* converter = new TaikoConverter();
Score* score = new Score();

//user inputs
std::string mapPath;
std::string musicPath;
std::string bgPath;
std::string musicFile;
std::string bgFile;
std::string ar;

std::string input;

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

	std::vector<Note*> notes = converter->makeNotes(gRenderer, mapPath, kb);

	music->loadMusic(musicPath);
	bg->loadBackground(gRenderer, bgPath, 50);
	//any AR from 1 to 4 is good for beginners.
	//TODO: let user input AR, map path, bg path, music path
	map->loadMap(gRenderer, notes, converter->getOverallDifficulty(mapPath), std::stoi(ar), kb);

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
}

int main(int argc, char* args[])
{
	//example map source: https://osu.ppy.sh/beatmapsets/146008#taiko/364949
	printf("\nWELCOME TO ALPHABET\n\n");
	while (true) {
		printf("Enter the full path of a taiko map (.osu file). \nOr, enter \"ex\" to load an example map. \nOr, enter \"quit\" to quit:\n>");
		std::getline(std::cin, input);
		if (input == "ex") {
			mapPath = "res/songs/nagi.osu";
			musicPath = "res/songs/nagi.mp3";
			bgPath = "res/songs/nagi.jpg";
		}
		else if (input == "quit") {
			break;
		}
		else {
			mapPath = input;
			musicFile = converter->getSongPath(input);
			bgFile = converter->getBackgroundPath(input);
			//truncate path until hit backslash
			while (!input.empty() && input[input.size() - 1] != '\\') {
				input.pop_back();
			}
			musicPath = input + musicFile;
			bgPath = input + bgFile;
		}

		printf("\nEnter the desired approach rate 1-10 (3 recommended for beginners), numerals only: \n>");
		//TODO: catch if user doesn't input a number
		std::getline(std::cin, ar);

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
				printf("\nPlaying... (close the game window to cancel the current session)\n\n");
				SDL_RaiseWindow(gWindow);

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
				score->reset();
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
							printf("Current session cancelled.\n\n");
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
						printf("RESULTS\n----------\nRANK: %s\nACCURACY: %.2f%%\nPERFECT: %i\nOK: %i\nMISS: %i\n\n",
							score->getRank().c_str(), score->getAccuracy(), score->getCount(2), score->getCount(1), score->getCount(0));
						break;
					}
				}
			}
		}
		//Free resources and close SDL
		close();
	}
	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}