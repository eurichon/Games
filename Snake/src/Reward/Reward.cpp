#include "../Reward/Reward.h"
#include "../Map/Map.h"
#include "../Snake/Snake.h"

Reward::Reward(Map *map)
{
	this->map = map;
	this->index = 0;
	this->points = 0;
}

void Reward::generatePosition()
{
	cout << "Generating new position" << endl;
	ofSeedRandom(ofGetElapsedTimeMicros());
	int free_space = pow(map->getMapSize(), 2) - map->getSnake()->getSize();

	int reward_index = ofRandom(free_space);
	position = map->getSnake()->findUncoveredPos(reward_index);
}

void Reward::draw()
{
	ofPushMatrix();
	ofTranslate(map->getMapRefPos().getX(), map->getMapRefPos().getY());
	ofPushMatrix();
	ofFill();
	int grid_size = map->getGridSize();
	int pos_x = (position.getX() + 0.5) * grid_size ;
	int pos_y = (position.getY() + 0.5) * grid_size ;
	ofTranslate(pos_x , pos_y );
	ofDrawCircle(0, 0, 0.5 * grid_size);
	ofPopMatrix();
	ofPopMatrix();
}

