#include "Map.h"


Map::Map(int size) : offset(50)
{
	if ((size % 2) == 0) {
		this->size = size + 1;
	}
	else {
		this->size = size;
	}
	dir = Vector2(1, 0);
	updateMap();
	setColors(ofColor(133, 205, 75), ofColor(65, 135, 14), ofColor(100, 99, 71));
	initReward();
	initSnake();
}

void Map::setColors(ofColor gridColorA, ofColor gridColorB, ofColor borderColor)
{
	this->borderColor = borderColor;
	this->gridColorA = gridColorA;
	this->gridColorB = gridColorB;
}

void Map::initSnake()
{
	snake = new SnakeDrawer(this);
}

void Map::initReward()
{
	reward = new Reward(this);
}

void Map::updateMap()
{
	int gui_size = 50;
	int width = ofGetWindowWidth();
	int height = ofGetWindowHeight();


	if (height > width) {
		int ref_pos_y = height - width + offset / 2;
		int ref_pos_x = offset / 2;
		cube_size = (width - offset) / size;
		refPosition = Vector2(ref_pos_x, ref_pos_y);
	}
}

void Map::draw()
{
	ofFill();
	ofSetLineWidth(1.0);
	ofPushMatrix(); {
		ofTranslate(refPosition.getX(), refPosition.getY());
		ofSetColor(borderColor);
		ofDrawRectangle(-offset / 2, -offset / 2, (cube_size*size) + offset, (cube_size*size) + offset);

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if ((i - j) % 2 == 0) {
					ofSetColor(gridColorA);
				}
				else {
					ofSetColor(gridColorB);
				}
				ofDrawRectangle(i*cube_size, j * cube_size, cube_size, cube_size);
			}
		}
	}
	ofPopMatrix();
}

bool Map::isPositionBelogsToMap(Vector2 pos)
{
	if (pos.getX() == -1 || pos.getY() == -1 || pos.getX() == size || pos.getY() == size) {
		return false;
	}
	else {
		return true;
	}
}

Vector2 Map::vectorToCoordinates(Vector2 v)
{
	return (v + 0.5)*cube_size;
}

Vector2 Map::indexToVector(int index)
{
	div_t v = div(index, size);
	return Vector2(v.quot, v.rem);

}

int Map::VectorToIndex(Vector2 v)
{
	return (v.getX()*size + v.getY());
}

Map::~Map()
{
	delete snake;
	delete reward;
}
