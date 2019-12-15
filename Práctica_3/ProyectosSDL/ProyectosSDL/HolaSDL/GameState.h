#pragma once
#include <list>
#include "GameObject.h"
#include "EventHandler.h"

class Game;

class GameState 
{
protected:
	list<GameObject*> objects;
	list<EventHandler*> events;
	Game* game;
public:
	GameState(list<GameObject*> objects, list<EventHandler*> events, Game* game);
	void update();
	void render();
	void handleEvents();
	void exitGame();
	bool getExit();
};