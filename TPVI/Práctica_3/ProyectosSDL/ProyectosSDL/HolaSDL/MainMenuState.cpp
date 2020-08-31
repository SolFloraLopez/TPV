#include "MainMenuState.h"
#include "SDLApplication.h"

MainMenuState::MainMenuState(SDLApplication* game) : GameState(game)
{
	buttonLoadTexture = GameState::getTexture(LoadButton);
	buttonExitTexture = GameState::getTexture(ExitButton);
	buttonPlayTexture = GameState::getTexture(PlayButton);

	MenuButton* buttonLoad = new MenuButton(buttonPos, BUTTON_WIDTH, BUTTON_HEIGHT, buttonLoadTexture, this, game->loadAction, game);
	MenuButton* buttonExit = new MenuButton({ buttonPos.getX() - 200, buttonPos.getY() }, BUTTON_WIDTH, BUTTON_HEIGHT, buttonExitTexture, this, game->exitAction, game);
	MenuButton* buttonPlay = new MenuButton({ buttonPos.getX() - 400, buttonPos.getY() }, BUTTON_WIDTH, BUTTON_HEIGHT, buttonPlayTexture, this, game->playAction, game);

	objects.push_back(buttonLoad);
	objects.push_back(buttonExit);
	objects.push_back(buttonPlay);

	events.push_back(buttonLoad);
	events.push_back(buttonExit);
	events.push_back(buttonPlay);
}

//MainMenuState::~MainMenuState() {
//	for (GameObject* ob : objects)
//	{
//		delete ob;
//	}
//};

//void MainMenuState::render()
//{
//	list<GameObject*>::iterator it;
//
//	it = objects.begin();
//
//	while (it != objects.end())
//	{
//		(*it)->render();
//		++it;
//	}
//}

void MainMenuState::handleEvents()
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