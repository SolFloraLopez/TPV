#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "Texture.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include "Balloon.h"
#include "Arrow.h"
#include "Bow.h"
#include "Butterfly.h"
#include "Reward.h"
#include "EventHandler.h"
#include "ScoreBoard.h"


using namespace std;

using uint = unsigned int;

enum { Background1, Background2, Background3, Background4, Background5, Background6,
	ScoreArrowTexture, DigitsTexture, BowTexture, Balloons, ArrowTexture, ButterflyTexture, RewardTexture, BubbleTexture};

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

const infoTexturas INFOTEXT[NUM_TEXTURES] = { {"..\\images\\bg1.png", 1, 1},
											{"..\\images\\bg_spring_trees_1.png", 1, 1},
											{"..\\images\\Cartoon_Forest_BG_01.png", 1, 1},
											{"..\\images\\Cartoon_Forest_BG_02.png", 1, 1},
											{"..\\images\\Cartoon_Forest_BG_03.png", 1, 1},
											{"..\\images\\Cartoon_Forest_BG_04.png", 1, 1},
											{"..\\images\\Arrow2.png", 1, 1},
											{"..\\images\\digits1.png", 1, 10},
											{"..\\images\\Bow2.png", 1, 1},
											{"..\\images\\balloons.png", 7, 6},
											{"..\\images\\Arrow1.png", 1, 1},
											{"..\\images\\butterfly2.png", 4, 10},
											{"..\\images\\rewards.png", 10, 8},
											{"..\\images\\bubble.png", 1, 1}
};

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit = false;
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
	

	vector<Arrow*> shotArrows;
	list<GameObject*> objects;
	list<EventHandler*> events;
	list<list<GameObject*>::iterator> objectsToErase;
	void balloonspawner();
	void butterflyspawner();
public:
	Game(bool load, string route);
	~Game();
	void run();
	void render();
	void handleEvents();
	void update();
	void saveToFile();
	void loadFromFile(string route);
	Arrow* collision(ArrowsGameObject* obj, int cols, int rows);
	void shoot(Arrow* arrow);
	int changeScore(int value);
	void rewardspawner(Point2D rewardPosition, Arrow* arrow);
	void killObject(list<GameObject*>::iterator object);
	void updateButterflyCounter();
	int changeAvaliableArrows(int amount);
	int changeCurrentArrows(int amount);
	bool getSaving();
	void exitGame();
	void writeData(string data);
};