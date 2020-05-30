#pragma once
#include "ArrowsGameObject.h"
#include <iostream>

class GameState;

class Balloon : public ArrowsGameObject{

private:
	int color;
	bool state = true;
	uint inst = 0;
	const int cols = 6;
	const int rows = 7;
	const int value = 5;
	

public:
	Balloon(Point2D pos, double width, double height, Vector2D vel, bool state, Texture* tex, int colour, PlayState* game, int ID);
	~Balloon();
	virtual void render() /*const*/;
	virtual void update();
	virtual void loadFromFile(fstream& input);
	virtual void saveToFile(ofstream& output);
	SDL_Rect* returnRect();
};