#pragma once
#include "GameState.h"
#include "Arrow.h"
#include "Reward.h"
#include <vector>

using uint = unsigned int;

enum {
	Background1, Background2, Background3, Background4, Background5, Background6,
	ScoreArrowTexture, DigitsTexture, BowTexture, Balloons, ArrowTexture, ButterflyTexture, RewardTexture, BubbleTexture
};

struct infoTexturas
{
	string route;
	int rows;
	int columns;
};

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 14;
const uint FRAME_RATE = 50;
const uint BASE_ARROWS_AMOUNT = 3;
const uint BASE_BUTTERFLY_AMOUNT = 3;
const uint BASE_POINT_MAX = 100;
const uint MAP_AMOUNT = 6;
const double BOW_VELOCITY = 5;
const double BALLOON_VELOCITY = 0.5;
const double ARROW_VELOCITY = 10;
const double BOW_HEIGHT = 61;
const double BOW_WIDTH = 142;

class PlayState : public GameState 
{
private:
	vector<Arrow*> shotArrows;
	list<list<GameObject*>::iterator> objectsToErase;
	bool recordingInput = false;
	bool saving = false;
	string file = "";
	Texture* textures[NUM_TEXTURES];
	int availableArrows = BASE_ARROWS_AMOUNT;
	int currentButterflies = 0;
	int currentArrows = 0;
	int points = 0;
	int currentMap = 0;
	int currentMaxPoints = BASE_POINT_MAX;
	bool load = false;
public:
	PlayState(list<GameObject*> objects, list<EventHandler*> events, Game* game);
	void update();
	void render();
	void handleEvents();
	Arrow* collision(ArrowsGameObject* obj, int cols, int rows);
	void shoot(Arrow* arrow);
	int changeScore(int value);
	void rewardspawner(Point2D rewardPosition, Arrow* arrow);
	void killObject(list<GameObject*>::iterator object);
	void updateButterflyCounter();
	int changeAvaliableArrows(int amount);
	int changeCurrentArrows(int amount);
	void exit();
};