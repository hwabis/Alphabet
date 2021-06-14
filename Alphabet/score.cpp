#include "score.h"

Score::Score() {
	missCount = 0;
	okCount = 0;
	perfCount = 0;
}

void Score::addCount(int type) {
	switch (type) {
	case 2:
		++perfCount;
		break;
	case 1:
		++okCount;
		break;
	case 0:
		++missCount;
		break;
	}
}

int Score::getCount(int type) {
	switch (type) {
	case 2:
		return perfCount;
	case 1:
		return okCount;
	case 0:
		return missCount;
	default:
		printf("Score::getCount invalid type\n");
		return -1;
	}
}

float Score::getAccuracy() {
	return (0.5f*(float)okCount + (float)perfCount) / 
		((float)missCount + (float)okCount + (float)perfCount) * 100;
}

std::string Score::getRank() {
	//https://osu.ppy.sh/wiki/en/FAQ#what-is-osu!taiko?
	float acc = getAccuracy();
	if (acc == 100) {
		return "SS";
	}
	else if (acc > 95) {
		return "S";
	}
	else if (acc > 90) {
		return "A";
	}
	else if (acc > 80) {
		return "B";
	}
	else {
		//seems like a leap, but real taiko has HP so that 
		//if you get "lower" than a B, then you wouldn't have passed anyway.
		return "F";
	}
}

void Score::reset() {
	missCount = 0;
	okCount = 0;
	perfCount = 0;
}