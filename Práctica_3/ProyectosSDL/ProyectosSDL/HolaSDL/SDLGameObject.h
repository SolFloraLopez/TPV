#pragma once
#include "GameObject.h"
#include "GameState.h"

class SDLGameObject : public GameObject {
	
private:
	Point2D pos;
	double width;
	double height;
	Texture* texture;
	GameState* gameState;
public:
	SDLGameObject(Point2D pos,double width,double height, Texture* texture, GameState* gameState);
	~SDLGameObject();
	virtual void render();
	virtual void update();
};