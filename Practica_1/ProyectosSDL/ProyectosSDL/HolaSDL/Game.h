#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "Texture.h"
#include <iostream>
#include <string>
#include <vector>
#include "Balloon.h"
#include "Arrow.h"
#include "Bow.h"


using namespace std;

using uint = unsigned int;

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 3;
const uint FRAME_RATE = 50;
const uint BOW_VELOCITY = 5;
const uint BALLOON_VELOCITY = 3;

enum {Background, BowTexture, Balloons};

struct infoTexturas
{
	string ruta;
	int filas;
	int columnas;
};

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit = false;
	//int points;
	//int arrows;
	Texture* textures[NUM_TEXTURES];
	Bow* bow;

	vector<Arrow*> shotArrows;
	vector<Balloon*> balloons;
	infoTexturas infoText[NUM_TEXTURES] = { {"..\\images\\bg1.png", 1, 1},
												{"..\\images\\Bow1.png", 1, 1},
												{"..\\images\\balloons.png", 7, 6} };
	void balloonspawner();
public:
	Game();
	~Game();
	void run();
	void render() const;
	void handleEvents();
	void update();
	//void collision();
	//void shoot();
};