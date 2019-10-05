#pragma once

#include "../Vector/Vector2.h"
#include "ofMain.h"

class Map;

class Reward
{
private:
	int points, index;

	Vector2 position;
	Map *map;

	const int time_step = 50;
public:
	Reward(Map *map);
	void generatePosition();
	inline Vector2 getPosition() { return position; }
	void draw();
};

