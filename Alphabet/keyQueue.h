#pragma once
#include <SDL.h>
#include <keyboard.h>
#include <texture.h>
#include <vector>
struct KeyQueue
{
	//this queue shows all notes that have spawned and not been hit/missed yet.
	//automatically updated by Map and Note
	std::vector<int> queue = {};

	SDL_Texture* digit1 = NULL;
	const std::string DIGIT1_PATH = "res/sprites/numbers/1.png";
	SDL_Texture* digit2 = NULL;
	const std::string DIGIT2_PATH = "res/sprites/numbers/2.png";
	SDL_Texture* digit3 = NULL;
	const std::string DIGIT3_PATH = "res/sprites/numbers/3.png";
	SDL_Texture* digit4 = NULL;
	const std::string DIGIT4_PATH = "res/sprites/numbers/4.png";
	SDL_Texture* digit5 = NULL;
	const std::string DIGIT5_PATH = "res/sprites/numbers/5.png";
	SDL_Texture* digit6 = NULL;
	const std::string DIGIT6_PATH = "res/sprites/numbers/6.png";
	SDL_Texture* digit7 = NULL;
	const std::string DIGIT7_PATH = "res/sprites/numbers/7.png";
	SDL_Texture* digit8 = NULL;
	const std::string DIGIT8_PATH = "res/sprites/numbers/8.png";

	//I'm gonna assume there's never gonna be more than 8 notes on the queue at a time... for now.
	//TODO: probably set a bound for custom duration so there can't be more than 8 on the screen

	bool loadKeys(SDL_Renderer* renderer) {
		bool success = true;

		//can i loop this... no?
		digit1 = Texture::loadTexture(DIGIT1_PATH,renderer);
		if (digit1 == NULL)
		{
			printf("Failed to load digit 1!\n");
			success = false;
		}
		digit2 = Texture::loadTexture(DIGIT2_PATH, renderer);
		if (digit1 == NULL)
		{
			printf("Failed to load digit 2!\n");
			success = false;
		}
		digit3 = Texture::loadTexture(DIGIT3_PATH, renderer);
		if (digit1 == NULL)
		{
			printf("Failed to load digit 3!\n");
			success = false;
		}
		digit4 = Texture::loadTexture(DIGIT4_PATH, renderer);
		if (digit1 == NULL)
		{
			printf("Failed to load digit 4!\n");
			success = false;
		}
		digit5 = Texture::loadTexture(DIGIT5_PATH, renderer);
		if (digit1 == NULL)
		{
			printf("Failed to load digit 5!\n");
			success = false;
		}
		digit6 = Texture::loadTexture(DIGIT6_PATH, renderer);
		if (digit1 == NULL)
		{
			printf("Failed to load digit 6!\n");
			success = false;
		}
		digit7 = Texture::loadTexture(DIGIT7_PATH, renderer);
		if (digit1 == NULL)
		{
			printf("Failed to load digit 7!\n");
			success = false;
		}
		digit8 = Texture::loadTexture(DIGIT8_PATH, renderer);
		if (digit1 == NULL)
		{
			printf("Failed to load digit 8!\n");
			success = false;
		}
		return success;
	}

	void render(SDL_Renderer* renderer, Keyboard* kb) {
		int index;
		for (int i = 0; i < queue.size(); ++i) {
			index = 0;
			for (int j = 0; j < kb->numberOfKeys; ++j) {
				if (kb->validKeys[j] == queue[i]) {
					index = j;
					break;
				}
			}
			SDL_Rect* pos = new SDL_Rect{ kb->key_positions[index].first, kb->key_positions[index].second, 104, 104 };


			switch (i) {
			case 0:
				SDL_RenderCopy(renderer, digit1, NULL, pos);
				break;
			case 1:
				SDL_RenderCopy(renderer, digit2, NULL, pos);
				break;
			case 2:
				SDL_RenderCopy(renderer, digit3, NULL, pos);
				break;
			case 3:
				SDL_RenderCopy(renderer, digit4, NULL, pos);
				break;
			case 4:
				SDL_RenderCopy(renderer, digit5, NULL, pos);
				break;
			case 5:
				SDL_RenderCopy(renderer, digit6, NULL, pos);
				break;
			case 6:
				SDL_RenderCopy(renderer, digit7, NULL, pos);
				break;
			case 7:
				SDL_RenderCopy(renderer, digit8, NULL, pos);
				break;
			}
		}
	}
};

