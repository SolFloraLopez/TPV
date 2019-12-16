#pragma once
#include "GameState.h"
#include "Balloon.h"
#include "Arrow.h"
#include "Reward.h"
#include "Butterfly.h"
#include <vector>
#include "Constants.h"

class PlayState : public GameState 
{
private:
	vector<Arrow*> shotArrows;
	list<list<GameObject*>::iterator> objectsToErase;
	bool recordingInput = false;
	bool saving = false;
	int availableArrows = BASE_ARROWS_AMOUNT;
	int currentButterflies = 0;
	int currentArrows = 0;
	int points = 0;
	int currentMap = 0;
	int currentMaxPoints = BASE_POINT_MAX;
	bool load = false;
	string file = "";
public:
	PlayState(list<GameObject*> objects, list<EventHandler*> events, SDLApplication* game);
	void update();
	void render();
	void handleEvents();
	void saveToFile(string file);
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