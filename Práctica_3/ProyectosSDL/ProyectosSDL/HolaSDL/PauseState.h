#pragma once
#include "GameState.h"
#include "MenuButton.h"

const Point2D saveButtonPos = { 700, 25 };
const double buttonWidth = 100; 
const double buttonHeight = 100;

class PauseState : public GameState
{
private:
	Texture* buttonTexture;
public:
	PauseState(SDLApplication* game);
	virtual void render() {};
	virtual void handleEvents() {};
	virtual void update() {};
	virtual void saveToFile(string file) {};
};