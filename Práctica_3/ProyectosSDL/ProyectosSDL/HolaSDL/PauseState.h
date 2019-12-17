#pragma once
#include "GameState.h"
#include "MenuButton.h"
#include <fstream>
#include <iostream>

class PauseState : public GameState
{
private:
	Texture* buttonSaveTexture;
	Texture* buttonResumeTexture;
	Texture* buttonMenuTexture;
public:
	PauseState(SDLApplication* game);
	virtual void render();
	virtual void handleEvents();
	virtual void update() {};
};