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
#include "GameStateMachine.h"
#include "PlayState.h"
#include "PauseState.h"
#include "Constants.h"


using namespace std;

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	GameStateMachine* stateMachine;
	bool exit = false;
	bool recordingInput = false; //
	bool saving = false; 
	string file = "";
	int availableArrows = BASE_ARROWS_AMOUNT;
	int currentButterflies = 0;
	int currentArrows = 0;
	int points = 0;
	int currentMap = 0;
	int currentMaxPoints = BASE_POINT_MAX;
	bool load = false; //
	

	vector<Arrow*> shotArrows;
	list<GameObject*> objects;
	list<EventHandler*> events;
	list<list<GameObject*>::iterator> objectsToErase;
	void balloonspawner();
	void butterflyspawner();
	Texture* textures[NUM_TEXTURES];

public:
	Game(bool load, string route);
	~Game();
	void run();
	void render();
	void handleEvents();
	void update();
	void saveToFile();
	void newSaveToFile();
	void loadFromFile(string route);
	Arrow* collision(ArrowsGameObject* obj, int cols, int rows); //
	void shoot(Arrow* arrow);
	int changeScore(int value);
	void rewardspawner(Point2D rewardPosition, Arrow* arrow);
	void killObject(list<GameObject*>::iterator object);
	void updateButterflyCounter();
	int changeAvaliableArrows(int amount);
	int changeCurrentArrows(int amount); //
	bool getSaving();
	bool getExit();
	void exitGame();
	Texture* getTexture(int num);
};