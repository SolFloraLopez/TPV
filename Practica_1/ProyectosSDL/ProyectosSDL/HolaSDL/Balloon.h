#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include <iostream>

class Game;

class Balloon {

private:
	Point2D pos;
	double ancho;
	double alto;
	int color;
	Vector2D vel;
	bool estado = true;
	uint inst = 0;
	Texture* texture = nullptr;
	Game* game;
	

public:
	Balloon(Point2D pos, double ancho, double alto, Vector2D vel, bool estado, Texture* tex, int color, Game* game);
	~Balloon();
	void render() const;
	bool update();
	SDL_Rect* returnRect();
};