//#include "Game.h"
//#include "Texture.h"
//#include <iostream>
//#include <string>
//
//using namespace std;
//
//using uint = unsigned int;
//
//Game::Game() {
//
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
//	SDL_Window* window = nullptr;
//	SDL_Renderer* renderer = nullptr;
//	const uint WIN_WIDTH = 800;
//	const uint WIN_HEIGHT = 600;
//	/*const uint FRAME_RATE = 500;*/
//
//	// We first initialize SDL
//	SDL_Init(SDL_INIT_EVERYTHING);
//	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
//		WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
//	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//	
//	string background = "..\\images\\background1.png";
//	Texture textureBackground(renderer, background, 1, 1);
//
//	if (window == nullptr || renderer == nullptr) throw "Error loading the SDL window or renderer";
//	// We now create the textures
//	for (uint i = 0; i < NUM_TEXTURES; i++) {
//		
//	}
//	// We finally create the game objects
//	dog = new Dog(...);
//	//helicopter = new Helicopter(…);
//}
//Game::~Game() {
//	for (uint i = 0; i < NUM_TEXTURES; i++) delete textures[i];
//	SDL_DestroyRenderer(renderer);
//	SDL_DestroyWindow(window);
//	SDL_Quit();
//}
//void Game::run() {
//	while (!exit) { // Falta el control de tiempo
//		handleEvents();
//		update();
//		render();
//	}
//}
//void Game::update() {
//	dog->update();
//	//...
//}
//void Game::render() const {
//	SDL_RenderClear(renderer);
//	dog->render();
//	//…
//		SDL_RenderPresent(renderer);
//}
//void Game::handleEvents() {
//	SDL_Event event;
//	while (SDL_PollEvent(&event) && !exit) {
//		if (event.type == SDL_QUIT) exit = true;
//		dog->handleEvents(event);
//		//...
//	}
//}