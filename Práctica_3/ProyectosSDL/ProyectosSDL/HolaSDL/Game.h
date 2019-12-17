#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "Texture.h"
#include "Vector2D.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>//
#include "Balloon.h"//
#include "Arrow.h"//
#include "Bow.h"//
#include "Butterfly.h"//
#include "Reward.h"//
#include "EventHandler.h"
#include "ScoreBoard.h"//
#include "GameStateMachine.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "EndState.h"
#include "Constants.h"
#include <time.h> /* */


using namespace std;

class SDLApplication {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	GameStateMachine* stateMachine;
	bool exit = false;
	Texture* textures[NUM_TEXTURES];

public:
	SDLApplication();
	~SDLApplication();
	void run();
	void render();
	void handleEvents();
	void update(){};
	void saveToFile();
	/* */void loadFromFile();
	bool getExit();
	void exitGame();
	Texture* getTexture(int num);
	void goMainMenu();
	void Pause();
	void Resume();
	void Play();
	void checkStateMachine();
	static void saveAction(SDLApplication* a) { a->saveToFile(); }
	static void loadAction(SDLApplication* a) { a->loadFromFile(); }
	static void mainMenuAction(SDLApplication* a) { a->goMainMenu(); }
	static void resAction(SDLApplication* a) { a->Resume(); }
	static void playAction(SDLApplication* a) { a->Play(); }
	static void exitAction(SDLApplication* a) { a->exitGame(); }
};