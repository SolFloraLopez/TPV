#pragma once
#include <list>
#include "GameObject.h"
#include "EventHandler.h"

class Game;

class GameState 
{
private:
	list<GameObject*> objects;
	list<EventHandler*> events;
	Game* game;
public:
	void update();
	void render();
	void handleEvents();
};