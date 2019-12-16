#pragma once
#include <list>
#include "GameObject.h"
#include "EventHandler.h"
#include "Texture.h"
#include "Constants.h"
#include <string>

class Game;

class GameState 
{
protected:
	list<GameObject*> objects;
	list<EventHandler*> events;
	Game* game;
public:
	GameState(Game* game);
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void handleEvents() = 0;
	virtual void saveToFile(string file) = 0;
	void exitGame();
	bool getExit();
	Texture* getTexture(int num);
};