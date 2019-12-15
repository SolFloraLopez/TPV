#pragma once
#include "SDLGameObject.h"
#include <iostream>
#include <fstream>
#include <list>

class Game;

class ArrowsGameObject : public SDLGameObject
{
protected:
	Vector2D vel;
	int ID;
	Texture* texture;
	list<GameObject*>::iterator it;

	ArrowsGameObject(Point2D pos, Vector2D vel, double width, double height, Texture* texture, Game* game, int ID);

public:
	virtual void render();
	virtual void update();
	SDL_Rect getDestRect(int cols, int rows);
	SDL_Rect* getCollisionRect(int cols, int rows);
	~ArrowsGameObject();
	void setItList(list<GameObject*>::iterator iterator);
	virtual void loadFromFile(fstream& input);
	virtual void saveToFile(ofstream& output);
};