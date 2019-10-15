#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include "Game.h"
#include "Texture.h"
#include "checkML.h"
#include <iostream>

using namespace std;

using uint = unsigned int;

Game::Game() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	for (int i = 0; i < NUM_TEXTURES; i++) 
	{
		textures[i] = new Texture(renderer, infoText[i].ruta, infoText[i].filas, infoText[i].columnas);
	}

	bow = new Bow({0,0}, (double)200, (double)190, { 0, 0.1 }, nullptr, textures[BowTexture], true);
}

void Game::run() {		//bucle principal
	while (!SDL_QuitRequested())
	{
		handleEvents();
		update();
		render();
	}
}

void Game::render() const 
{
	SDL_RenderClear(renderer);
	textures[Background]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });
	bow->render();
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

void Game::balloonspawner() {};

void Game::update() 
{
	bow->update();
};