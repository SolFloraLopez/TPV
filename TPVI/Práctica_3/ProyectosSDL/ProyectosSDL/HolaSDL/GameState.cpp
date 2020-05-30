#include "SDLApplication.h"
#include "GameState.h"

GameState::GameState(SDLApplication* game) : game(game) {}

GameState::~GameState() 
{
	for (GameObject* ob : objects)
	{
		delete ob;
	}

	objects.clear();
};

void GameState::exitGame()
{
	game->exitGame();
}

bool GameState::getExit()
{
	return game->getExit();
}

Texture* GameState::getTexture(int num)
{
	return game->getTexture(num);
}

void GameState::loadFromFile()
{
	game->loadFromFile();
}

void GameState::saveToFile()
{
	game->saveToFile();
}

void GameState::Pause() {
	game->Pause();
}

void GameState::Resume() {
	game->Resume();
}

void GameState::End() {
	game->End();
}