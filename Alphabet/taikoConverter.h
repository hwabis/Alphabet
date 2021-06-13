#pragma once
#include <SDL.h>
#include <keyboard.h>
#include <vector>
#include <note.h>
#include <fStream>
#
struct TaikoConverter
{
	//why not make a standard converter?
	//I think taiko is more appropriate for this gamemode since
	//taiko maps only focus on rhythm, whereas std maps often 
	//dumb-down their rhythm in return for spacing patterns...
	std::vector<Note*> makeNotes(SDL_Renderer* renderer, std::string path, Keyboard* kb) {
		std::vector<Note*> notes = {};

		//check if valid taiko map
		bool foundTaiko = false;
		std::ifstream file(path);

		if (file.is_open()) {

			bool findHitObjects = false;
			std::string line;
			//get the third number in each, or after the second comma
			int commaCount;
			std::string hitTime = "";
			while (std::getline(file, line)) {
				if (line == "Mode: 1") {
					foundTaiko = true;
				}
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
					//is there a better way to determine notes...?
					srand(std::stoi(hitTime));
					note->loadNote(renderer, std::stof(hitTime), kb->validKeys[rand() % kb->numberOfKeys], kb);
					notes.push_back(note);
				}
			}
			file.close();
		}
		
		if (!foundTaiko) {
			printf("Warning: not a valid taiko map!\n");
		}

		return notes;
	}

	float getOverallDifficulty(std::string path) {
		std::string OD = "";

		std::ifstream file(path);
		if (file.is_open()) {

			std::string line;
			while (std::getline(file, line)) {
				if (line.substr(0,18) == "OverallDifficulty:") {
					//line[18] to the end is the OD
					for (int i = 18; i < line.length(); ++i) {
						OD += line[i];
					}
				}
			}
			file.close();
		}
		return std::stof(OD);
	}
};