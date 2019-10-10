#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include "Dog.h"
#include "Texture.h"
#include <iostream>
#include <string>

using namespace std;

using uint = unsigned int;

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 3;
//...

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	// uint winWidth, winHeight; // También podrían estar aquí
	Dog* dog = nullptr;
	//Helicopter* helicopter = nullptr;
	bool exit = false;
	Texture* textures[NUM_TEXTURES];
public:
	Game();
	~Game();
	void run();
	void render() const;
	void handleEvents();
	void update();
};
