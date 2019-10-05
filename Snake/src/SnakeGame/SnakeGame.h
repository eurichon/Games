#pragma once

#include "ofxGui.h"
#include "../Vector/Vector2.h"
#include "../Map/Map.h"
#include "../Snake/SnakeDrawer.h"
#include "../Reward/Reward.h"


#define dT 450

class Vector2;

class SnakeGame
{
	bool start_game;
	ofxPanel *gui;
	Map *map;
	Vector2 key_direction;
	ofxLabel *label;
	string score;
public:
	SnakeGame();
	~SnakeGame();
	void update();
	void draw();
	void readKeyboard(int key);
};

