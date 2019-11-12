#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include <iostream>

class Arrow {
private:
	double width;
	double height;
	Point2D position;
	Vector2D vel;
	Texture* texture = nullptr;
public:
	Arrow(double alto, double ancho, Point2D pos, Vector2D vel,Texture* tex);
	~Arrow();
	void render() const;
	void changePos(Vector2D pos);
	bool update();
	SDL_Rect* returnPointRect();
};