#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "Texture.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Balloon.h"
#include "Arrow.h"
#include "Bow.h"


using namespace std;

using uint = unsigned int;

enum { Background, BowTexture, Balloons, ArrowTexture };

struct infoTexturas
{
	string route;
	int rows;
	int columns;
};

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 4;
const uint FRAME_RATE = 50;
const uint BALLOON_POINTS = 10;
const double BOW_VELOCITY = 5;
const double BALLOON_VELOCITY = 0.5;
const double ARROW_VELOCITY = 4;

const infoTexturas INFOTEXT[NUM_TEXTURES] = { {"..\\images\\bg1.png", 1, 1},
											{"..\\images\\Bow2.png", 1, 1},
											{"..\\images\\balloons.png", 7, 6},
											{"..\\images\\Arrow1.png", 1, 1} };

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
	vector<Balloon*> balloons;
	void balloonspawner();
public:
	Game();
	~Game();
	void run();
	void render() const;
	void handleEvents();
	void update();
	bool collision(Balloon* balloon);
	void shoot(Arrow* arrow);
	int getAvailableArrows();
};