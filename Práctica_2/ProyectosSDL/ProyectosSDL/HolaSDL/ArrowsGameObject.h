#pragma once
#include "GameObject.h"
#include <list>

class Game;

class ArrowsGameObject : public GameObject
{
protected:
	Point2D pos;
	Vector2D vel;
	double width;
	double height;
	int currentData = 0;
	Texture* texture;
	Game* game;
	list<GameObject*>::iterator it;

	ArrowsGameObject(Point2D pos, Vector2D vel, double width, double height, Texture* texture, Game* game);

public:
	void render();
	void update();
	SDL_Rect getDestRect(int cols, int rows);
	SDL_Rect* getCollisionRect(int cols, int rows);
	~ArrowsGameObject();
	void setItList(list<GameObject*>::iterator iterator);
	//void loadFromFile(string data);
	//saveToFile();
};