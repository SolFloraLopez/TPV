#pragma once
#include "ArrowsGameObject.h"
#include <iostream>

class Arrow : public ArrowsGameObject {
private:
	int numHits = 0;
public:
	Arrow(double alto, double ancho, Point2D pos, Vector2D vel, Texture* tex, GameState* game, int ID);
	~Arrow();
	void changePos(Vector2D pos);
	virtual void update();
	virtual void loadFromFile(fstream& input);
	virtual void saveToFile(ofstream& output);
	SDL_Rect* returnPointRect();
	void addHit();
	int getHits();
};