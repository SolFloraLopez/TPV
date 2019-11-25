#pragma once
#include "ArrowsGameObject.h"
#include <iostream>

class Game;

class Balloon : public ArrowsGameObject{

private:
	/*Point2D pos;
	double width;
	double height;*/
	int color;
	//Vector2D vel;
	bool state = true;
	uint inst = 0;
	//Texture* texture = nullptr;
	//Game* game;
	

public:
	Balloon(Point2D pos, double width, double height, Vector2D vel, bool state, Texture* tex, int colour, Game* game);
	~Balloon();
	void render() /*const*/;
	bool update();
	SDL_Rect* returnRect();
};