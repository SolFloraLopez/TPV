#include "PauseState.h"

PauseState::PauseState(Game* game) : GameState(game)
{
	buttonTexture =  GameState::getTexture(Button);
	 objects.push_back(new MenuButton(saveButtonPos, buttonWidth, buttonHeight, buttonTexture, game));
}

