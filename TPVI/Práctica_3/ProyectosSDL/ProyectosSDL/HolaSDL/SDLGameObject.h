#pragma once
#include "GameObject.h"
#include "GameState.h"
#include <list>

class SDLGameObject : public GameObject {
	
protected:
	Point2D pos;
	double width;
	double height;
	Texture* texture;
	GameState* game;
	list<GameObject*>::iterator it;
public:
	SDLGameObject(Point2D pos,double width,double height, Texture* texture, GameState* gameState);
	virtual void render();
	//virtual void update() = 0;
	virtual void saveToFile(ofstream& output) = 0;
	virtual void loadFromFile(fstream& input) = 0;
	SDL_Rect getDestRect(int cols, int rows);
	void setItList(list<GameObject*>::iterator iterator);
};