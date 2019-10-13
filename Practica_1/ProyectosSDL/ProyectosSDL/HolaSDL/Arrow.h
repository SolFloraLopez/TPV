#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include <iostream>

class Arrow {
private:
	double ancho;
	double alto;
	Point2D position;
	Vector2D vel;
	Texture* texture = nullptr;
public:
	Arrow(double alto, double ancho, Point2D pos, Vector2D vel,Texture* tex);
	void render() const;
	void rect();
	bool update();

	
};