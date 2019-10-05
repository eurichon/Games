#include "SnakeGame.h"



SnakeGame::SnakeGame()
{
	gui = new ofxPanel();
	gui->setup("Menu", "setting.xml");
	gui->setSize(200, 50);

	start_game = false;
	key_direction = Vector2(1,0);
	map = new Map(15);
	label = new ofxLabel();
	label->setSize(100, 50);
	map->getSnake()->hasDied(&start_game);
	score = "0";
}


void SnakeGame::draw()
{
	gui->draw();
	map->updateMap();
	map->draw();

	if (start_game) {
		score = ofToString(map->getSnake()->getSize() - 5);
		map->getSnake()->animate(key_direction);
		map->getReward()->draw();
		
	}

	ofPushMatrix();
	ofTranslate(ofGetWindowWidth() - 100, 0);
	label->setup(" Score", score, 100, 50);
	label->setBorderColor(ofColor::blue);
	label->setBackgroundColor(ofColor(64, 200, 200));
	label->draw();
	ofPopMatrix();

}

void SnakeGame::readKeyboard(int key)
{
	switch (key)
	{
	case ' ':
		if (!start_game) {
			start_game = true;
			map->getReward()->generatePosition();
		}
		break;
	case OF_KEY_UP:
		key_direction = Vector2(0, -1);
		break;
	case OF_KEY_DOWN:
		key_direction = Vector2(0, 1);
		break;
	case OF_KEY_LEFT:
		key_direction = Vector2(-1, 0);
		break;
	case OF_KEY_RIGHT:
		key_direction = Vector2(1, 0);
		break;
	case 'm':
		break;
	default:
		break;
	}
}

void SnakeGame::update()
{
	
}

SnakeGame::~SnakeGame()
{
}


