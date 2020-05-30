#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include <iostream>

class Game;

class Balloon {

private:
	Point2D pos;
	double width;
	double height;
	int color;
	Vector2D vel;
	bool state = true;
	uint inst = 0;
	Texture* texture = nullptr;
	Game* game;
	

public:
	Balloon(Point2D pos, double width, double height, Vector2D vel, bool state, Texture* tex, int color, Game* game);
	~Balloon();
	void render() const;
	bool update();
	SDL_Rect* returnRect();
};