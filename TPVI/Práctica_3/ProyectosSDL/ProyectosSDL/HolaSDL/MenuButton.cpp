#include "MenuButton.h"

MenuButton::MenuButton(Point2D pos, double width, double height, Texture* texture, GameState* gameState, CallBackOnClick* thisAction, SDLApplication* thisGame) :
	SDLGameObject(pos, width, height, texture, gameState) 
{
	action = thisAction;
	game = thisGame;
}

void MenuButton::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
	{
		SDL_Point p = { event.button.x, event.button.y };
		if (SDL_PointInRect(&p, &getDestRect(1, 1)) == SDL_TRUE)
		{
			action(game);
		}
	}
}