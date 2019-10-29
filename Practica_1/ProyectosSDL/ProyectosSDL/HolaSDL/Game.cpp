#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include "Game.h"
#include "Texture.h"
#include <iostream>
#include <time.h>

using namespace std;

using uint = unsigned int;

Game::Game() {
	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	for (int i = 0; i < NUM_TEXTURES; i++) 
	{
		textures[i] = new Texture(renderer, infoText[i].ruta, infoText[i].filas, infoText[i].columnas);
	}

	bow = new Bow({0,0}, (double)82, (double)190, { 0, BOW_VELOCITY }, textures[BowTexture], textures[ArrowTexture], true, this);
	balloons.push_back(new Balloon({ WIN_HEIGHT, WIN_HEIGHT }, (double)512, (double)512, { -1, BALLOON_VELOCITY }, true, textures[Balloons], rand() % 10, this));
}

void Game::run() {		//bucle principal
	while (!SDL_QuitRequested())
	{
		handleEvents();
		balloonspawner();
		update();
		render();
		SDL_Delay(1000 / FRAME_RATE);
	}
}

void Game::render() const 
{
	SDL_RenderClear(renderer);
	textures[Background]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });

	bow->render();

	for (int i = 0; i < shotArrows.size(); i++)
	{
		shotArrows[i]->render();
	}

	for (int i = 0; i < balloons.size(); i++) 
	{
		balloons[i]->render();
	}
	
	SDL_RenderPresent(renderer);
};

void Game::handleEvents() 
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) exit = true;
		bow->handleEvents(event);
	}
}

void Game::balloonspawner() 
{
	if (balloons.size() < 1000 && rand() % 20 == 1)
	{
		balloons.push_back(new Balloon({ ((double)WIN_WIDTH / 2) + rand() % (WIN_WIDTH / 2), WIN_HEIGHT }, 
			(double)512, (double)512, { -1, BALLOON_VELOCITY}, true, textures[Balloons], rand() % 7, this));
	}
};

void Game::shoot(Arrow* arrow)
{
	shotArrows.push_back(arrow);
	availableArrows--;
}

int Game::getAvailableArrows()
{
	return availableArrows;
}

bool Game::collision(Balloon* balloon)
{
	for (int i = 0; i < shotArrows.size(); i++)
	{
		if (SDL_HasIntersection(balloon->returnRect(), shotArrows[i]->returnPointRect()))
		{
			return true;
		}
	}

	return false;
}

void Game::update()
{
	bow->update();
	for (int i = 0; i < balloons.size(); i++)
	{
		if (balloons[i]->update() == false) 
		{
			balloons.erase(balloons.begin() + i);
		}
	}

	for (int i = 0; i < shotArrows.size(); i++)
	{
		if (shotArrows[i]->update() == false)
		{
			balloons.erase(balloons.begin() + i);
		}
	}
}

Game::~Game() 
{
	for (int i = 0; i < balloons.size(); i++) {
		balloons[i]->~Balloon();
	}
	
	balloons.clear();
	bow->~Bow();

	for (uint i = 0; i < NUM_TEXTURES; i++) delete textures[i];
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
