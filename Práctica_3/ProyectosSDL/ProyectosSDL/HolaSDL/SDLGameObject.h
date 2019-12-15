#pragma once
#include "GameObject.h"
#include "GameState.h"

class SDLGameObject : public GameObject {
	
protected:
	Point2D pos;
	double width;
	double height;
	Texture* texture;
	Game* game;
public:
	SDLGameObject(Point2D pos,double width,double height, Texture* texture, Game* gameState);
	virtual void render() = 0;
	virtual void update() = 0;
	virtual void saveToFile(ofstream& output) = 0;
	virtual void loadFromFile(fstream& input) = 0;
};