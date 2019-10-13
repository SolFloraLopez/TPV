#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Arrow.h"
#include <iostream>

class Bow {

private:
	Point2D pos;
	double ancho;
	double alto;
	Vector2D vel;
	Arrow* arrow = nullptr;
	Texture* texture = nullptr;
	
	//Game* game = nullptr;

public:
	Bow(Point2D pos, double ancho, double alto, Vector2D vel, Arrow* arrow, Texture* texture);
	void render() const;
	void update();
	void handleEvents(/*SDL_Event& event*/);


};