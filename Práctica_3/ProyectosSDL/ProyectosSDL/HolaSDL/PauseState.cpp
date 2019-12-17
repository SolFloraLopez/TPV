#include "PauseState.h"
#include "Game.h"

PauseState::PauseState(SDLApplication* game) : GameState(game)
{
	buttonSaveTexture =  GameState::getTexture(Button);
	buttonResumeTexture =  GameState::getTexture(Button);
	buttonMenuTexture =  GameState::getTexture(Button);

	MenuButton* buttonResume = new MenuButton(buttonPos, BUTTON_WIDTH, BUTTON_HEIGHT, buttonResumeTexture, this, game->resAction, game);
	MenuButton* buttonMenu = new MenuButton({ buttonPos.getX() - 200, buttonPos.getY() }, BUTTON_WIDTH, BUTTON_HEIGHT, buttonMenuTexture, this, game->mainMenuAction, game);
	MenuButton* buttonSave = new MenuButton({ buttonPos.getX() - 400, buttonPos.getY() }, BUTTON_WIDTH, BUTTON_HEIGHT, buttonSaveTexture, this, game->saveAction, game);

	objects.push_back(buttonResume);
	objects.push_back(buttonMenu);
	objects.push_back(buttonSave);

	events.push_back(buttonResume);
	events.push_back(buttonMenu);
	events.push_back(buttonSave);
}

void PauseState::render()
{
	list<GameObject*>::iterator it;

	it = objects.begin();

	while (it != objects.end())
	{
		(*it)->render();
		++it;
	}
}

void PauseState::handleEvents()
{
	SDL_Event event;

	if (!events.empty())
	{
		while (SDL_PollEvent(&event)) 
		{
			list<EventHandler*>::iterator eh;

			eh = events.begin();

			while (eh != events.end())
			{
				(*eh)->handleEvent(event);
				++eh;
			}
		}
	}
}
