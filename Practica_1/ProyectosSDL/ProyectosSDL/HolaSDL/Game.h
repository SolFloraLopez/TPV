#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "Texture.h"
#include <iostream>
#include <string>

using namespace std;

using uint = unsigned int;

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 3;
const uint FRAME_RATE;

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit = false;
	int points;
	int arrows;
	Texture* textures[NUM_TEXTURES];
	void balloonspawner();
	
public:
	Game();
	~Game();
	void run();
	void render() const;
	void handleEvents();
	void update();
	void collision();
	void shoot();
};