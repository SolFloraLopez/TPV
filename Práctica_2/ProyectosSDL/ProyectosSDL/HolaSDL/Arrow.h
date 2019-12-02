#pragma once
#include "ArrowsGameObject.h"
#include <iostream>

class Arrow : public ArrowsGameObject {
private:
	int numHits = 0;
public:
	Arrow(double alto, double ancho, Point2D pos, Vector2D vel, Texture* tex, Game* game);
	~Arrow();
	//void render() const;
	void changePos(Vector2D pos);
	void update();
	SDL_Rect* returnPointRect();
	void addHit();
	int getHits();
};