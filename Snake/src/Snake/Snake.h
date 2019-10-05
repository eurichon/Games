#ifndef SNAKE_H
#define SNAKE_H 

#define SPEED 4
#define OFFSET 40
#define SNAKE_INIT_SIZE 5

#include "ofMain.h"
#include "../Vector/Vector2.h"
#include <list>

class Map;

class Snake {
protected:
	int size;
	float speed;
	bool just_got_point;

	Vector2 direction, pre_tail;
	Map *map;

	list<Vector2> body;
	list<int> body_index;

	bool updateBody(Vector2 new_head);
	float getLength();
public:
	Snake(Map *map);
	void initSnake(int size, Vector2 pos);
	void updateDirection(Vector2 new_direction);
	bool move();
	void updateSpeed();
	inline float getSpeed() { return speed; }
	inline int getSize() { return size; }
	Vector2 findUncoveredPos(int index);
};

#endif // SNAKE_H
