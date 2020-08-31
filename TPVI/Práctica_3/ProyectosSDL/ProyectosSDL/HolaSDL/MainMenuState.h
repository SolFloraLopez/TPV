#pragma once
#include "GameState.h"
#include "MenuButton.h"

class MainMenuState : public GameState 
{
private:
	Texture* buttonLoadTexture;
	Texture* buttonPlayTexture;
	Texture* buttonExitTexture;
public:
	MainMenuState(SDLApplication* game);
	//~MainMenuState();
	//virtual void update() {};
	//virtual void render();
	virtual void handleEvents();
};