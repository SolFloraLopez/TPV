#pragma once
#include "GameState.h"
#include "Balloon.h"
#include "Arrow.h"
#include "Reward.h"
#include "Butterfly.h"
#include "ScoreBoard.h"
#include "Bow.h"
#include <vector>
#include "Constants.h"
#include "FileFormatError.h"
#include "FileNotFoundError.h"
#include "SDLError.h"


class PlayState : public GameState 
{
private:
	list<Arrow*> shotArrows;
	list<list<GameObject*>::iterator> objectsToErase;
	bool saving = false;
	int availableArrows = BASE_ARROWS_AMOUNT;
	int currentButterflies = 0;
	int currentArrows = 0;
	int points = 0;
	int currentMap = 0;
	int currentMaxPoints = BASE_POINT_MAX;
	bool load = false;
	string file = "";
	void newGame();
public:
	PlayState(SDLApplication* game, string file);
	PlayState(SDLApplication* game) : GameState(game) { newGame(); };
	virtual void update();
	virtual void render();
	virtual void handleEvents();
	virtual void saveToFile();
	void loadFromFile(string file);
	Arrow* collision(ArrowsGameObject* obj, int cols, int rows);
	void shoot(Arrow* arrow);
	int changeScore(int value);
	void rewardspawner(Point2D rewardPosition, Arrow* arrow);
	void balloonspawner();
	void butterflySpawner();
	void killObject(list<GameObject*>::iterator object);
	void updateButterflyCounter();
	int changeAvaliableArrows(int amount);
	int changeCurrentArrows(int amount);
};