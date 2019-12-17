#pragma once
#include "GameState.h"
#include "MenuButton.h"

class EndState : public GameState
{
private:
	Texture* buttonMainTexture;
	Texture* buttonExitTexture;
public:
	EndState(SDLApplication* game);
	~EndState();
	virtual void render();
	virtual void update() {};
	virtual void handleEvents();
};