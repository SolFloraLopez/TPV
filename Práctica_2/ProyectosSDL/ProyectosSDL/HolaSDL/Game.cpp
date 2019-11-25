#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include "Game.h"
#include "Texture.h"
#include <iostream>
#include <time.h>

using namespace std;

using uint = unsigned int;

Game::Game() 
{
	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (window == nullptr || renderer == nullptr) throw "SDL Error \n";

	for (int i = 0; i < NUM_TEXTURES; i++) //Crea el array de texturas con las texturas de todo el juego
	{
		textures[i] = new Texture(renderer, INFOTEXT[i].route, INFOTEXT[i].rows, INFOTEXT[i].columns);
	}

	bow = new Bow({0,0}, (double)82, (double)190, { 0, BOW_VELOCITY }, textures[BowTexture], textures[ArrowTexture], true, this); //Crea el arco
	butterfly = new Butterfly({ 100,100 }, { 0.5,0.5 }, (double)384, (double)368, true, textures[ButterflyTexture], this);
}

void Game::run() {//Bucle principal
	while (!SDL_QuitRequested() && !exit)
	{
		handleEvents();
		balloonspawner();
		update();
		render();
		SDL_Delay(1000 / FRAME_RATE);
	}
}

void Game::render() const //Llama a los metodos render de los elementos del juego
{
	SDL_RenderClear(renderer);
	textures[Background]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });

	bow->render();
	butterfly->render();
	

	for (uint i = 0; i < shotArrows.size(); i++)
	{
		shotArrows[i]->render();
	}

	for (uint i = 0; i < balloons.size(); i++) 
	{
		balloons[i]->render();
	}
	
	SDL_RenderPresent(renderer);
};

void Game::handleEvents() //Llama a HandleEvents del bow mientras que exit sea false, mientras que el jugador no salga del juego
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) exit = true;
		bow->handleEvent(event);
	}
}

void Game::balloonspawner() //Generador de globos
{
	if (balloons.size() < 1000 && rand() % 20 == 1)
	{
		balloons.push_back(new Balloon({ ((double)WIN_WIDTH / 2) + rand() % (WIN_WIDTH / 2), WIN_HEIGHT }, 
			(double)512, (double)597, { -1, 2 + (rand() % 4) * BALLOON_VELOCITY}, true, textures[Balloons], rand() % 7, this));
	}
};

void Game::shoot(Arrow* arrow) //Añade la flecha al array de flechas lanzadas y resta uno a las flechas disponibles
{
	shotArrows.push_back(arrow);
	availableArrows--;
	cout << "\n Arrows: " << availableArrows;
}

int Game::getAvailableArrows() //Devuelve el numero de flechas disponibles
{
	return availableArrows;
}

bool Game::collision(ArrowsGameObject* object,int cols, int rows) //Calcula la colision entre flechas y globos para todas la flechas lanzadas
{
	for (uint i = 0; i < shotArrows.size(); i++) 
	{
		if (SDL_HasIntersection(object->getCollisionRect(cols,rows), shotArrows[i]->returnPointRect())) 
		{
			return true;
		}
	}

	return false;
}

void Game::changeScore(int value)
{
	points += value;
	cout << value;
}

void Game::update() //Llama a los update de los elementos del juego, si estos devuelven false se elimina el elemento correspondiente
{
	bow->update();
	for (uint i = 0; i < balloons.size();)
	{
		if (!balloons[i]->update())
		{
			delete balloons[i];
			balloons.erase(balloons.begin() + i);
		}

		else i++;
	}

	for (uint i = 0; i < shotArrows.size();)
	{
		if (!shotArrows[i]->update())
		{
			delete shotArrows[i];
			shotArrows.erase(shotArrows.begin() + i);

			if (availableArrows == 0 && shotArrows.size() < 1)
			{
				exit = true;
			}
		}

		else i++;
	}
}

Game::~Game() //Destructor del juego
{
	for (uint i = 0; i < balloons.size(); i++) {
		delete balloons[i];
	}
	
	balloons.clear();
	delete bow;

	for (uint i = 0; i < NUM_TEXTURES; i++) delete textures[i];
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
