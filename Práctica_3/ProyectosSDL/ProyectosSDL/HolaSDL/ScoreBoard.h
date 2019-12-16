#pragma once
#include "GameObject.h"
#include "PlayState.h"
#include "Vector2D.h"
#include <list>

class SDLApplication;

class ScoreBoard : public SDLGameObject 
{
private:
	const uint numberHeight = 20;
	const uint numberWidth = 200;
	const uint numberCols = 10;
	const uint arrowHeight = 75;
	const uint arrowWidth = 15;
	const Point2D scorePos = { 700, 25 };
	const Point2D arrowPos = {15, 0};

	int points = 0;
	int arrowsAmount = 0;

	GameState* game;
	Texture* numbersTex;
	Texture* arrowTex;

	PlayState* playState;

	list<GameObject*>::iterator it;
public:
	ScoreBoard(Texture* numbers, Texture* arrows, GameState* game);
	virtual void render();
	virtual void update();
	virtual void loadFromFile(fstream& input);
	virtual void saveToFile(ofstream& output);
	SDL_Rect getDestRect(int cols, int rows, uint height, uint width, Vector2D pos);
	void setItList(list<GameObject*>::iterator iterator);
};

