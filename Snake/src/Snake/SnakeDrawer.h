#pragma once
#include "Snake.h"

class SnakeDrawer : public Snake
{
private:
	long time_interval, dt,inc_size_timer;
	float step,iterations,curr_index;

	
	int curr_size;
	int inc_index;
	vector<Vector2> curr_body;
	ofColor pattern[5];
	bool start_animation;
	bool start_inc;
	bool *is_alive;

	void updateValues();
public:
	SnakeDrawer(Map *map);
	void init();
	Vector2 getLinePos(float percentage,int offset);
	Vector2 getPositionInLine(float offset);
	void resetIterator();
	void drawBody();
	void drawHead();
	void animate(Vector2 key_direction);
	void hasDied(bool *state);
	~SnakeDrawer();
};

