#include "MainMenuState.h"

MainMenuState::MainMenuState(SDLApplication* game) : GameState(game)
{
	buttonTexture = GameState::getTexture(Button);
	objects.push_back(new MenuButton(ButtonPos, buttonWidth, buttonHeight, buttonTexture, game));
}