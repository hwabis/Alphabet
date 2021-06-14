#include <taikoConverter.h>

std::vector<Note*> TaikoConverter::makeNotes(SDL_Renderer* renderer, std::string path, Keyboard* kb) {
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
				if (hitTime != "") {
					note->loadNote(renderer, std::stof(hitTime), kb->validKeys[rand() % kb->numberOfKeys], kb);
				}
				notes.push_back(note);
			}
		}
		file.close();
	}

	if (!foundTaiko) {
		printf("Not a valid taiko map! Notes may not be generated correctly. Double-check the path.\n");
	}

	return notes;
}

float TaikoConverter::getOverallDifficulty(std::string path) {
	std::string OD = "";

	bool odFound = false;

	std::ifstream file(path);
	if (file.is_open()) {

		std::string line;
		while (std::getline(file, line)) {
			if (line.substr(0, 18) == "OverallDifficulty:") {
				odFound = true;
				for (int i = 18; i < line.length(); ++i) {
					OD += line[i];
				}
			}
		}
		file.close();
	}
	if (!odFound) {
		return 0;
	}
	else {
		return std::stof(OD);
	}
}

std::string TaikoConverter::getSongPath(std::string path) {
	std::string songPath = "";

	bool pathFound = false;

	std::ifstream file(path);
	if (file.is_open()) {

		std::string line;
		while (std::getline(file, line)) {
			if (line.substr(0, 15) == "AudioFilename: ") {
				pathFound = true;
				for (int i = 15; i < line.length(); ++i) {
					songPath += line[i];
				}
			}
		}
		file.close();
	}
	//music class will handle if it's an invalid path... it really should never be
	return songPath;
}

std::string TaikoConverter::getBackgroundPath(std::string path) {
	std::string bgPath = "";

	//looking for "//Background and Video events", then get path from the line after that
	bool lineFound = false;

	std::ifstream file(path);
	if (file.is_open()) {

		std::string line;
		while (std::getline(file, line)) {
			if (line == "//Background and Video events") {
				lineFound = true;
			}
			else if (lineFound == true) {
				//the path should be after "0,0,"" up to the next """
				int i = 5;
				while (line[i] != '"') {
					bgPath += line[i];
					++i;
				}
				break;
			}
		}
		file.close();
	}
	//bg class will handle if it's an invalid path... it really should never be
	return bgPath;
}