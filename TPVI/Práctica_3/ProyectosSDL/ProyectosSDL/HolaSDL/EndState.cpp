#include "EndState.h"
#include "SDLApplication.h"

EndState::EndState(SDLApplication* game) : GameState(game)
{
	buttonMainTexture = GameState::getTexture(MainButton);
	buttonExitTexture = GameState::getTexture(ExitButton);

	MenuButton* buttonMainMenu = new MenuButton(buttonPos, BUTTON_WIDTH, BUTTON_HEIGHT, buttonMainTexture, this, game->mainMenuAction, game);
	MenuButton* buttonExit = new MenuButton({ buttonPos.getX() - 200, buttonPos.getY() }, BUTTON_WIDTH, BUTTON_HEIGHT, buttonExitTexture, this, game->exitAction, game);

	objects.push_back(buttonMainMenu);
	objects.push_back(buttonExit);

	events.push_back(buttonMainMenu);
	events.push_back(buttonExit);

}
/*EndState::~EndState() {
	for (GameObject* ob : objects)
	{
		delete ob;
	}
}*/;

//void EndState::render()
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

void EndState::handleEvents()
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