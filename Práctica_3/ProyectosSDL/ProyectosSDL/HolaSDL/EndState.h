#pragma once
#include "GameState.h"

class EndState : public GameState
{
	void render();
	void handleEvents();
	virtual void saveToFile() {};
	virtual void loadFromFile() {};
};