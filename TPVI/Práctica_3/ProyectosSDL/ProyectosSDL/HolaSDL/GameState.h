#pragma once
#include <list>
#include "GameObject.h"
#include "EventHandler.h"
#include "Texture.h"
#include "Constants.h"
#include <string>

class SDLApplication;

class GameState 
{
protected:
	list<GameObject*> objects;
	list<EventHandler*> events;
	SDLApplication* game;
public:
	GameState(SDLApplication* game) : game(game) {};
	~GameState();
	virtual void update();
	virtual void render();
	virtual void handleEvents() = 0;

	virtual void saveToFile() ;
	virtual void loadFromFile() ;
	void exitGame();
	bool getExit();
	Texture* getTexture(int num);

	void Pause() ;
	void Resume() ;
	void End() ;
};