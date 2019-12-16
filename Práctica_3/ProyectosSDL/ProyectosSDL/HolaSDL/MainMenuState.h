#pragma once
#include "GameState.h"
#include "MenuButton.h"

const Point2D ButtonPos = { 700, 25 };
const double buttonWidth = 100;
const double buttonHeight = 100;

class MainMenuState : public GameState 
{
private:
	Texture* buttonTexture;
public:
	MainMenuState(SDLApplication* game);
	virtual void render() {};
	virtual void handleEvents() {};
};