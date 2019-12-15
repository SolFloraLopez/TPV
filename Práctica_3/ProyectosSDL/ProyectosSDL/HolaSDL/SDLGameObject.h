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
	~SDLGameObject();
	virtual void render();
	virtual void update();
	virtual void saveToFile(ofstream& output);
	virtual void loadFromFile(fstream& input);
};