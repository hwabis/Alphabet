#pragma once
#include <SDL.h>
#include <keyboard.h>
#include <vector>
#include <note.h>
#include <fStream>
struct TaikoConverter
{
	std::vector<Note*> makeNotes(SDL_Renderer* renderer, std::string path, Keyboard* kb) {
		std::vector<Note*> notes = {};

		std::ifstream file(path);
		if (file.is_open()) {

			bool findHitObjects = false;
			std::string line;
			//get the third number in each, or after the second comma
			int commaCount;
			std::string hitTime = "";
			while (std::getline(file, line)) {
				if (!findHitObjects) {
					if (line == "[HitObjects]") {
						findHitObjects = true;
					}
				}
				else {
					commaCount = 0;
					hitTime = "";
					for (int i = 0; i < line.length(); ++i) {
						if (line[i] == ',') {
							++commaCount;
						}
						else if (commaCount == 2) {
							hitTime += line[i];
						}
						else if (commaCount == 3) {
							break;
						}
					}
					Note* note = new Note();
					//TODO: get duration from map AR, make key not random
					note->loadNote(renderer, std::stof(hitTime), 3000, kb->validKeys[rand() % kb->numberOfKeys]);
					notes.push_back(note);
				}
			}
			file.close();
		}
		
		return notes;
	}
};