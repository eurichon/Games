#include "../Snake/Snake.h"
#include "../Map/Map.h"


//to combine and index generation for reward
bool Snake::updateBody(Vector2 new_head)
{	
	//convert vectors to indexes
	this->pre_tail = body.front();
	int index_to_add = map->VectorToIndex(new_head);
	int index_to_del = map->VectorToIndex(pre_tail);

	//add the new head and pop the tail
	body.push_back(new_head);
	if (!just_got_point) {
		body.pop_front();
	}
	
	bool is_valid = true;
	bool added = false;

	//if they are the same the sorted list remains the same and the move if valid
	if (index_to_add == index_to_del && !just_got_point) {
		return is_valid;
	}
	list<int>::iterator it, it_add, it_del;
	it = body_index.begin();
	while (it != body_index.end()) {
		//position to add the head in the sorted list found
		if ((*it) > index_to_add && !added) {
			body_index.insert(it, index_to_add);
			added = true;
		}
		else if ((*it) == index_to_add) {
			is_valid = false;
		}
		if ((*it) == index_to_del && !just_got_point) {
			body_index.erase(it++); //first increment the iterator and then remove the previous element
		}
		else {
			it++;
		}
	}
	if (!added) {
		body_index.push_back(index_to_add);
	}
	just_got_point = false;
	return is_valid;
}


float Snake::getLength()
{
	return ((size - 1) * (map->getGridSize()));
}


Snake::Snake(Map *map)
{
	direction = Vector2(1, 0);
	this->map = map;
	this->initSnake(SNAKE_INIT_SIZE, Vector2(0,(int)(map->getMapSize() / 2 )));
}

void Snake::initSnake(int size, Vector2 pos)
{
	this->just_got_point = false;
	this->size = size;
	this->direction = Vector2(1, 0);
	body.clear();
	body_index.clear();
	for (int i = 0; i < size; i++) {
		Vector2 temp_pos = pos + Vector2(i, 0);
		this->body.push_back(temp_pos);
		this->body_index.push_back(map->VectorToIndex(temp_pos));
	}
	this->pre_tail = body.front();
	this->updateSpeed();
	//this->map->resetGame();
}

bool Snake::move()
{
	Vector2 head = body.back();
	Vector2 reward_pos = map->getReward()->getPosition();
	head = head + direction;
	
	if (!map->isPositionBelogsToMap(head)) {
		this->initSnake(SNAKE_INIT_SIZE, Vector2(0, (map->getMapSize() / 2)));
		return false;
	}
	else {
		if (head == reward_pos) {
			just_got_point = true;
			size++;
			
			if (updateBody(head)) {
				updateSpeed();
				map->getReward()->generatePosition();
				return true;
			}
			else {
				initSnake(SNAKE_INIT_SIZE, Vector2(0, (map->getMapSize() / 2)));
				return false;
			}
		}
		else {
			if (updateBody(head)) {
				updateSpeed();
				return true;
			}
			else {
				initSnake(SNAKE_INIT_SIZE, Vector2(0, (map->getMapSize() / 2)));
				return false;
			}
		}
	}
}

void Snake::updateDirection(Vector2 new_direction)
{
	float angle = getArg(direction, new_direction,Angle_units::degrees);
	if (angle == 180) {
		return;
	}
	direction.rotate(angle, Angle_units::degrees);
	direction.setX((int)(direction.getX()));
	direction.setY((int)(direction.getY()));
}

void Snake::updateSpeed()
{ 
	speed = 0.5 * log((size - 3)) + 1;
}

Vector2 Snake::findUncoveredPos(int index)
{
	list<int>::iterator it;
	for (it = body_index.begin(); it != body_index.end(); ++it) {
		if ((*it) <= index) {
			index = index + 1;
		}
		else {
			break;
		}
	}
	return map->indexToVector(index);
}


