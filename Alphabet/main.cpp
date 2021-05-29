//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <utility>
#include <keyboard.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture(std::string path);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

Keyboard* kb = new Keyboard();

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
			}
		}
	}
	kb->initKeyboard();

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load keyboard texture
	kb->gKeyboardTexture = loadTexture(kb->KEYBOARD_PATH);
	if (kb->gKeyboardTexture == NULL)
	{
		printf("Failed to load keyboard image!\n");
		success = false;
	}

	//Load keyDown texture
	kb->gKeyDownTexture = loadTexture(kb->KEYDOWN_PATH);
	if (kb->gKeyDownTexture == NULL)
	{
		printf("Failed to load keydown image!\n");
		success = false;
	}

	return success;
}

void close()
{
	kb->destroy();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
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

			bool keyIsDown = false;
			SDL_Rect* keyDownPos = new SDL_Rect{0, 0, kb->KEYDOWN_DIM, kb->KEYDOWN_DIM};

			//While application is running
			while (!quit)
			{
				//Clear screen
				SDL_RenderClear(gRenderer);

				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN && kb->isValidKey(e.key.keysym.sym))
					{
						kb->setKeyDownPos(keyDownPos, e);
						SDL_RenderCopy(gRenderer, kb->gKeyDownTexture, NULL, keyDownPos);
						keyIsDown = true;
					}
					else if (e.type == SDL_KEYUP)
					{
						keyIsDown = false;
					}
				}

				if (keyIsDown) {
					SDL_RenderCopy(gRenderer, kb->gKeyDownTexture, NULL, keyDownPos);
				}

				//Render keyboard texture to screen
				SDL_RenderCopy(gRenderer, kb->gKeyboardTexture, NULL, NULL);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}