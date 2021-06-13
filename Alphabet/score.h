#pragma once
#include <stdio.h>
class Score
{
	int missCount;
	int okCount;
	int perfCount;
public:
	Score();
	//2 = perfect, 1 = ok, 0 = miss
	void addCount(int countType);
	int getCount(int countType);
	float getAccuracy();
	void reset();
};

