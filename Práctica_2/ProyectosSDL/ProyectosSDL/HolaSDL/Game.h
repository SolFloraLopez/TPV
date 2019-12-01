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


using namespace std;

using uint = unsigned int;

enum { Background, BowTexture, Balloons, ArrowTexture , ButterflyTexture, RewardTexture, BubbleTexture};

struct infoTexturas
{
	string route;
	int rows;
	int columns;
};

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 7;
const uint FRAME_RATE = 50;
const uint BUTTERFLY_AMOUNT = 12;
const double BOW_VELOCITY = 5;
const double BALLOON_VELOCITY = 0.5;
const double ARROW_VELOCITY = 8;

const infoTexturas INFOTEXT[NUM_TEXTURES] = { {"..\\images\\bg1.png", 1, 1},
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
	Texture* textures[NUM_TEXTURES];
	Bow* bow;
	int availableArrows = 10;
	int points = 0;
	

	vector<Arrow*> shotArrows;
	list<GameObject*> objects;
	list<list<GameObject*>::iterator> objectsToErase;
	void balloonspawner();
	void butterflyspawner();
public:
	Game();
	~Game();
	void run();
	void render();
	void handleEvents();
	void update();
	Arrow* collision(ArrowsGameObject* obj, int cols, int rows);
	void changeScore(int value);
	void shoot(Arrow* arrow);
	int getAvailableArrows();
	void rewardspawner(Point2D rewardPosition, Arrow* arrow);
	void killObject(list<GameObject*>::iterator object);
};