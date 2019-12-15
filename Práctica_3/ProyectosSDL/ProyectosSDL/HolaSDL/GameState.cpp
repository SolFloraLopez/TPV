#include "Game.h"
#include "GameState.h"

GameState::GameState(list<GameObject*> objects, list<EventHandler*> events, Game* game) : objects(objects), events(events), game(game) {}

void GameState::exitGame()
{
	game->exitGame();
}

bool GameState::getExit()
{
	return game->getExit();
}