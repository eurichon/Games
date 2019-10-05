#pragma once

#include "ofMain.h"
#include "../Reward/Reward.h"
#include "../Snake/SnakeDrawer.h"


class Vector2;

class Map
{
	const int offset;
	int size,
		cube_size;
	Reward *reward;
	SnakeDrawer *snake;
	Vector2 refPosition, dir;
	ofColor gridColorA, 
			gridColorB, 
			borderColor;
	
public:
	Map(int size);
	void setColors(ofColor gridColorA, ofColor gridColorB, ofColor borderColor);
	void initSnake();
	void initReward();
	void updateMap();
	void draw();
	bool isPositionBelogsToMap(Vector2 pos);
	Vector2 vectorToCoordinates(Vector2 v);
	Vector2 indexToVector(int index);
	int VectorToIndex(Vector2 v);
	inline SnakeDrawer* getSnake() { return snake; }
	inline Reward* getReward() { return reward; }
	inline int getMapSize() { return size; }
	inline int getGridSize() { return cube_size; }
	inline Vector2 getMapRefPos() { return refPosition; }
	~Map();
};

