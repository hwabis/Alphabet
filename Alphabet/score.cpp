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
	case -1:
		printf("Score::getCount invalid type");
		return -1;
	}
}

float Score::getAccuracy() {
	return (0.5f*(float)okCount + (float)perfCount) / 
		((float)missCount + (float)okCount + (float)perfCount)
		* 100 ;
}

void Score::reset() {
	missCount = 0;
	okCount = 0;
	perfCount = 0;
}