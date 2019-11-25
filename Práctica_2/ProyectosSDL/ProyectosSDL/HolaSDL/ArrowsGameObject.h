#pragma once
#include "GameObject.h"

class Game;

class ArrowsGameObject : public GameObject
{
protected:
	Point2D pos;
	Vector2D vel;
	double width;
	double height;
	//int iterador;
	Texture* texture;
	Game* game;

	ArrowsGameObject(Point2D pos, Vector2D vel, double width, double height, Texture* texture, Game* game);

public:
	void render();
	bool update();
	SDL_Rect getDestRect(int cols, int rows);
	SDL_Rect* getCollisionRect(int cols, int rows);
	~ArrowsGameObject();
	//loadFromFile();
	//saveToFile();
};