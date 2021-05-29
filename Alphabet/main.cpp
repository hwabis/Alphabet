//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <utility>

//Screen dimension constants
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

const std::string KEYBOARD_PATH = "res/kb.png";
const std::string KEYDOWN_PATH = "res/keydown.png";

const int KEYDOWN_DIM = 104;

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

//Keyboard texture
SDL_Texture* gKeyboardTexture = NULL;

//Keydown texture
SDL_Texture* gKeyDownTexture = NULL;

enum key_names {
	q, w, e, r, t, y, u, i, o, p, leftBracket, rightBracket, 
	a, s, d, f, g, h, j, k, l, semicolon, quote,
	z, x, c, v, b, n, m, comma, period, slash,
	spacebar, numberOfKeys
};

std::pair<int, int> key_positions[numberOfKeys];

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

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load keyboard texture
	gKeyboardTexture = loadTexture(KEYBOARD_PATH);
	if (gKeyboardTexture == NULL)
	{
		printf("Failed to load keyboard image!\n");
		success = false;
	}

	//Load keyDown texture
	gKeyDownTexture = loadTexture(KEYDOWN_PATH);
	if (gKeyDownTexture == NULL)
	{
		printf("Failed to load keydown image!\n");
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded keyboard image
	SDL_DestroyTexture(gKeyboardTexture);
	gKeyboardTexture = NULL;

	//Free loaded keydown image
	SDL_DestroyTexture(gKeyDownTexture);
	gKeyDownTexture = NULL;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
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

	for (int i = 0; i < 12; ++i)
		key_positions[i] = std::make_pair(9 + 113 * i, 270);
	for (int i = 12; i < 23; ++i) 
		key_positions[i] = std::make_pair(37 + 113 * (i - 12), 383);
	for (int i = 23; i < 33; ++i)
		key_positions[i] = std::make_pair(95 + 113 * (i - 23), 496);
	key_positions[33] = std::make_pair(265, 609);

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
			SDL_Rect* keyDownPos = new SDL_Rect{0, 0, KEYDOWN_DIM, KEYDOWN_DIM};

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
					else if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
							//is there a better way to do this lol
							case SDLK_q:
								keyDownPos->x = key_positions[key_names::q].first;
								keyDownPos->y = key_positions[key_names::q].second;
								break;
							case SDLK_w:
								keyDownPos->x = key_positions[key_names::w].first;
								keyDownPos->y = key_positions[key_names::w].second;
								break;
							case SDLK_e:
								keyDownPos->x = key_positions[key_names::e].first;
								keyDownPos->y = key_positions[key_names::e].second;
								break;
							case SDLK_r:
								keyDownPos->x = key_positions[key_names::r].first;
								keyDownPos->y = key_positions[key_names::r].second;
								break;
							case SDLK_t:
								keyDownPos->x = key_positions[key_names::t].first;
								keyDownPos->y = key_positions[key_names::t].second;
								break;
							case SDLK_y:
								keyDownPos->x = key_positions[key_names::y].first;
								keyDownPos->y = key_positions[key_names::y].second;
								break;
							case SDLK_u:
								keyDownPos->x = key_positions[key_names::u].first;
								keyDownPos->y = key_positions[key_names::u].second;
								break;
							case SDLK_i:
								keyDownPos->x = key_positions[key_names::i].first;
								keyDownPos->y = key_positions[key_names::i].second;
								break;
							case SDLK_o:
								keyDownPos->x = key_positions[key_names::o].first;
								keyDownPos->y = key_positions[key_names::o].second;
								break;
							case SDLK_p:
								keyDownPos->x = key_positions[key_names::p].first;
								keyDownPos->y = key_positions[key_names::p].second;
								break;
							case SDLK_LEFTBRACKET:
								keyDownPos->x = key_positions[key_names::leftBracket].first;
								keyDownPos->y = key_positions[key_names::leftBracket].second;
								break;
							case SDLK_RIGHTBRACKET:
								keyDownPos->x = key_positions[key_names::rightBracket].first;
								keyDownPos->y = key_positions[key_names::rightBracket].second;
								break;
							case SDLK_a:
								keyDownPos->x = key_positions[key_names::a].first;
								keyDownPos->y = key_positions[key_names::a].second;
								break;
							case SDLK_s:
								keyDownPos->x = key_positions[key_names::s].first;
								keyDownPos->y = key_positions[key_names::s].second;
								break;
							case SDLK_d:
								keyDownPos->x = key_positions[key_names::d].first;
								keyDownPos->y = key_positions[key_names::d].second;
								break;
							case SDLK_f:
								keyDownPos->x = key_positions[key_names::f].first;
								keyDownPos->y = key_positions[key_names::f].second;
								break;
							case SDLK_g:
								keyDownPos->x = key_positions[key_names::g].first;
								keyDownPos->y = key_positions[key_names::g].second;
								break;
							case SDLK_h:
								keyDownPos->x = key_positions[key_names::h].first;
								keyDownPos->y = key_positions[key_names::h].second;
								break;
							case SDLK_j:
								keyDownPos->x = key_positions[key_names::j].first;
								keyDownPos->y = key_positions[key_names::j].second;
								break;
							case SDLK_k:
								keyDownPos->x = key_positions[key_names::k].first;
								keyDownPos->y = key_positions[key_names::k].second;
								break;
							case SDLK_l:
								keyDownPos->x = key_positions[key_names::l].first;
								keyDownPos->y = key_positions[key_names::l].second;
								break;
							case SDLK_SEMICOLON:
								keyDownPos->x = key_positions[key_names::semicolon].first;
								keyDownPos->y = key_positions[key_names::semicolon].second;
								break;
							case SDLK_QUOTE:
								keyDownPos->x = key_positions[key_names::quote].first;
								keyDownPos->y = key_positions[key_names::quote].second;
								break;
							case SDLK_z:
								keyDownPos->x = key_positions[key_names::z].first;
								keyDownPos->y = key_positions[key_names::z].second;
								break;
							case SDLK_x:
								keyDownPos->x = key_positions[key_names::x].first;
								keyDownPos->y = key_positions[key_names::x].second;
								break;
							case SDLK_c:
								keyDownPos->x = key_positions[key_names::c].first;
								keyDownPos->y = key_positions[key_names::c].second;
								break;
							case SDLK_v:
								keyDownPos->x = key_positions[key_names::v].first;
								keyDownPos->y = key_positions[key_names::v].second;
								break;
							case SDLK_b:
								keyDownPos->x = key_positions[key_names::b].first;
								keyDownPos->y = key_positions[key_names::b].second;
								break;
							case SDLK_n:
								keyDownPos->x = key_positions[key_names::n].first;
								keyDownPos->y = key_positions[key_names::n].second;
								break;
							case SDLK_m:
								keyDownPos->x = key_positions[key_names::m].first;
								keyDownPos->y = key_positions[key_names::m].second;
								break;
							case SDLK_COMMA:
								keyDownPos->x = key_positions[key_names::comma].first;
								keyDownPos->y = key_positions[key_names::comma].second;
								break;
							case SDLK_PERIOD:
								keyDownPos->x = key_positions[key_names::period].first;
								keyDownPos->y = key_positions[key_names::period].second;
								break;
							case SDLK_SLASH:
								keyDownPos->x = key_positions[key_names::slash].first;
								keyDownPos->y = key_positions[key_names::slash].second;
								break;
							case SDLK_SPACE:
								keyDownPos->x = key_positions[key_names::spacebar].first;
								keyDownPos->y = key_positions[key_names::spacebar].second;
								break;
						}

						SDL_RenderCopy(gRenderer, gKeyDownTexture, NULL, keyDownPos);
						keyIsDown = true;
					}
					else if (e.type == SDL_KEYUP)
					{
						keyIsDown = false;
					}
				}

				if (keyIsDown) {
					SDL_RenderCopy(gRenderer, gKeyDownTexture, NULL, keyDownPos);
				}

				//Render keyboard texture to screen
				SDL_RenderCopy(gRenderer, gKeyboardTexture, NULL, NULL);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}