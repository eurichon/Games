#include "SnakeDrawer.h"
#include "../Map/Map.h"


void SnakeDrawer::updateValues()
{
	this->time_interval = 250 / getSpeed();
	this->iterations = (float)(time_interval) / 20;
	this->step = (float)(map->getGridSize()) / iterations;
}

SnakeDrawer::SnakeDrawer(Map *map):Snake(map)
{
	init();
	pattern[0] = ofColor(82,75,47);
	pattern[1] = ofColor(177,148,43);
	pattern[2] = ofColor(177,43,57);
	pattern[3] = ofColor(177, 148, 43);
	pattern[4] = ofColor(82, 75, 47);//ofColor(193, 118, 18);
}

void SnakeDrawer::init()
{
	this->inc_size_timer = ofGetElapsedTimeMillis();
	this->dt = ofGetElapsedTimeMillis();
	this->updateValues();
	this->inc_index = 0;
	this->start_inc = false;
	this->curr_size = size;
	this->start_animation = false;
	this->curr_index = 0;
}

Vector2 SnakeDrawer::getLinePos(float percentage,int offset)
{
	int grid_size = map->getGridSize();

	if (percentage < 0 || percentage > 1.0) {
		return Vector2(0, 0);
	}
	else if (percentage == 1) {
		Vector2 new_head, pre_head, curr_direction;
		list<Vector2>::reverse_iterator rit;
		new_head = body.back();
		rit = body.rbegin();
		rit++;
		pre_head = (*rit);
		curr_direction = new_head - pre_head;
		return ((pre_head + 0.5)*grid_size + curr_direction * offset);
	}
	else {
		float wanted_distance = percentage * (curr_size - 1) * grid_size;
		list<Vector2>::iterator it = body.begin();
		Vector2 new_tail = (*it);
		Vector2 curr_direction = new_tail - pre_tail;
		Vector2 tail = (pre_tail + 0.5)*grid_size + curr_direction * offset;


		for (it = body.begin(); it != body.end(); ++it) {
			Vector2 curr_tail = ((*it) + 0.5)*grid_size;

			curr_direction = (curr_tail - tail);
			float curr_distance = curr_direction.getNorm();
	
			if (curr_distance < wanted_distance) {
				wanted_distance = wanted_distance - curr_distance;
			}
			else {
				curr_direction.normalize();
				return (tail + curr_direction * wanted_distance);
			}
			tail = curr_tail;
		}
	}
}



Vector2 SnakeDrawer::getPositionInLine(float offset)
{
	int vector_size = curr_body.size();
	unsigned int i = vector_size;
	float distance = 0;
	Vector2 head, tail;
	do {
		if (i == 1) {
			return map->vectorToCoordinates(curr_body.at(0));
		}
		i--;
		offset = offset - distance;
		head = curr_body.at(i);
		tail = curr_body.at(i - 1);
		distance = (head - tail).getNorm() * map->getGridSize();
	} while (offset > distance);
	
	Vector2 curr_direction = tail - head;
	curr_direction.normalize();
	Vector2 position = map->vectorToCoordinates(curr_body.at(i)) + curr_direction * offset;

	return position;
}
	

void SnakeDrawer::resetIterator()
{
	curr_body.clear();
	curr_body.push_back(pre_tail);
	list<Vector2>::iterator it = body.begin();
	for (; it != body.end(); ++it) {
		curr_body.push_back(*it);
	}
	
}

void SnakeDrawer::drawBody()
{
	ofPushMatrix();
	ofTranslate(map->getMapRefPos().getX(),map->getMapRefPos().getY());
	int grid_size = map->getGridSize();
	int number_of_steps = 3 * curr_size + 1;
	float total_length = (curr_size - 1) * grid_size;
	float step = total_length / number_of_steps;
	float offset = (1.0 - curr_index / iterations) * grid_size;
	float cicle_size;
	resetIterator();

	if (inc_index == number_of_steps) {
		start_inc = true;
	}

	if (start_inc) {
		number_of_steps = inc_index;
		if (number_of_steps == 3 * size + 1) {
			start_inc = false;
			inc_index = 0;
			curr_size = size;
			start_animation = false;
		}
	}

	for (int i = 1; i <= number_of_steps; i++) {
		if (i == 3) {
			this->drawHead();
		}
		Vector2 center = getPositionInLine((i-1)*step + offset);
		ofPushMatrix();
		ofTranslate(center.getX(), center.getY());
		int color_index = i % 5;
		ofSetColor(pattern[color_index]);
		if (i == inc_index) {
			cicle_size = 1.4*ofMap(i, 0, number_of_steps, 0.4*grid_size, 0.35*grid_size);
		}
		else {
			cicle_size = ofMap(i, 0, number_of_steps, 0.4*grid_size, 0.35*grid_size);
		}
		
		ofDrawCircle(0, 0, cicle_size);
		ofPopMatrix();
	}	
	ofPopMatrix();
}



void SnakeDrawer::drawHead()
{
	int grid_size = map->getGridSize();
	float offset = -curr_index / iterations * grid_size + grid_size;
	Vector2 head_pos = getPositionInLine(offset);
	Vector2 ref_direction = Vector2(1, 0);
	ofSetColor(ofColor(196,9,9));
	ofPushMatrix();
	ofTranslate(head_pos.getX(), head_pos.getY());
	float angle = getArg(ref_direction, direction, Angle_units::degrees);
	ofRotateDeg(angle);
	ofDrawEllipse(0, 0, 1.2*grid_size, 0.9*grid_size );
	ofSetColor(ofColor::papayaWhip);
	Vector2 left_eye, right_eye;
	left_eye = Vector2(5, grid_size / 6);
	right_eye = Vector2(5, -grid_size / 6);
	ofDrawCircle(left_eye.getX(), left_eye.getY(), grid_size / 7);
	ofDrawCircle(right_eye.getX(), right_eye.getY(),grid_size / 7);


	Vector2 reward_pos = map->getReward()->getPosition();
	reward_pos = map->vectorToCoordinates(reward_pos);
	//left eye
	ofPushMatrix();
	ofTranslate(left_eye.getX(),left_eye.getY());
	Vector2 eye_pos = head_pos;
	Vector2 look_direction = reward_pos - eye_pos;
	look_direction.normalize();
	ofRotateDeg(-angle);
	ofSetColor(ofColor::black);
	ofDrawCircle(look_direction.getX() * grid_size / 16, look_direction.getY() * grid_size / 16, grid_size / 13);
	ofPopMatrix();

	ofPushMatrix();
	ofTranslate(right_eye.getX(), right_eye.getY());
	eye_pos = head_pos;
	look_direction = reward_pos - eye_pos;
	look_direction.normalize();
	ofRotateDeg(-angle);
	ofSetColor(ofColor::black);
	ofDrawCircle(look_direction.getX() * grid_size / 16, look_direction.getY() *grid_size / 16, grid_size / 13);
	ofPopMatrix();


	ofPopMatrix();
}

void SnakeDrawer::animate(Vector2 key_direction)
{
	
	if (size >= curr_size + 1) {
		start_animation = true;
	}
	else if (size < curr_size) {
		curr_size = size;
	}
	updateValues();
	
	if ((ofGetElapsedTimeMillis() - dt) > 20) {
		dt = ofGetElapsedTimeMillis();
		if (curr_index + 1 < iterations) {
			curr_index = curr_index + 1;
		}
		else {
			this->updateDirection(key_direction);
			if (!move()) {
				init();
				*is_alive = false;
				return;
			}
			curr_index = 0;
		}
	}
	
	if ((ofGetElapsedTimeMillis() - inc_size_timer) > 30 && start_animation) {
		inc_size_timer = ofGetElapsedTimeMillis();
		inc_index++;
	}
	this->drawBody(); 
}

void SnakeDrawer::hasDied(bool *state)
{
	is_alive = state;
}

SnakeDrawer::~SnakeDrawer()
{
}
