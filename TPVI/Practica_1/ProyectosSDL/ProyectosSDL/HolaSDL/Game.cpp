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
		ifstream route (infoText[i].route);

		if (!route.is_open()) throw "Texture file route is not valid \n";

		else textures[i] = new Texture(renderer, infoText[i].route, infoText[i].rows, infoText[i].columns);
	}

	bow = new Bow({0,0}, (double)82, (double)190, { 0, BOW_VELOCITY }, textures[BowTexture], textures[ArrowTexture], true, this); //Crea el arco
	
}

void Game::run() {		//Bucle principal
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
		bow->handleEvents(event);
	}
}

void Game::balloonspawner() //Generador de globos
{
	if (balloons.size() < 1000 && rand() % 20 == 1)
	{
		balloons.push_back(new Balloon({ ((double)WIN_WIDTH / 2) + rand() % (WIN_WIDTH / 2), WIN_HEIGHT }, 
			(double)512, (double)512, { -1, 2 + (rand() % 4) * BALLOON_VELOCITY}, true, textures[Balloons], rand() % 7, this));
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

bool Game::collision(Balloon* balloon) //Calcula la colision entre flechas y globos para todas la flechas lanzadas
{
	for (uint i = 0; i < shotArrows.size(); i++) 
	{
		if (SDL_HasIntersection(balloon->returnRect(), shotArrows[i]->returnPointRect())) 
		{
			points += BALLOON_POINTS;
			cout << "\n Points: " << points;
			return true;
		}
	}

	return false;
}

void Game::update() //Llama a los update de los elementos del juego, si estos devuelven false se elimina el elemento correspondiente
{
	bow->update();

	for (uint i = 0; i < balloons.size(); i++)
	{
		if (balloons[i]->update() == false) 
		{
			balloons.erase(balloons.begin() + i);
		}
	}

	for (uint i = 0; i < shotArrows.size(); i++)
	{
		if (shotArrows[i]->update() == false)
		{
			shotArrows.erase(shotArrows.begin() + i);

			if(availableArrows == 0 && shotArrows.size() < 1) 
			{
				exit = true;
			}
		}
	}
}

Game::~Game() //Destructor del juego
{
	for (uint i = 0; i < balloons.size(); i++) {
		balloons[i]->~Balloon();
	}
	
	balloons.clear();
	bow->~Bow();

	for (uint i = 0; i < NUM_TEXTURES; i++) delete textures[i];
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
