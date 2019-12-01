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

	bow = new Bow({ 0,0 }, (double)82, (double)190,
	{ 0, BOW_VELOCITY }, textures[BowTexture], textures[ArrowTexture], true, this); //Crea el arco

		objects.push_back(bow);
	bow->setItList(objects.end());

	butterflyspawner();
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

void Game::render() //Llama a los metodos render de los elementos del juego
{
	SDL_RenderClear(renderer);
	textures[Background]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });

	list<GameObject*>::iterator it;

	it = objects.begin();

	while (it != objects.end())
	{
		(*it)->render();
		++it;
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
	if (rand() % 20 == 1)
	{
		Balloon* newBalloon = new Balloon({ ((double)WIN_WIDTH / 2) + rand() % (WIN_WIDTH / 2), WIN_HEIGHT }, (double)512,
			(double)597, { -1, 2 + (rand() % 4) * BALLOON_VELOCITY }, true, textures[Balloons], rand() % 7, this);

		objects.push_back(newBalloon);
		newBalloon->setItList(objects.end());
	}
};

void Game::butterflyspawner() //Generador de globos
{
	for (int i = 0; i < BUTTERFLY_AMOUNT; i++)
	{
		Butterfly* newButterfly = new Butterfly({ ((double)WIN_WIDTH / 3) + rand() % (WIN_WIDTH / 3), (double)(rand() % (WIN_HEIGHT - 92)) },
			{ 1 - (double)(rand() % 2) * 2 , 1 - (double)(rand() % 2) * 2 }, (double)384, (double)368, true, textures[ButterflyTexture], this);

		objects.push_back(newButterfly);
		newButterfly->setItList(objects.end());
	}
};

void Game::rewardspawner(Point2D rewardPosition, Arrow* arrow)
{
	Reward* newReward = new Reward({ rewardPosition.getX() + 20, rewardPosition.getY() + 20}, { 0, 1 },
		(double)352, (double)238, true, textures[RewardTexture], textures[BubbleTexture], arrow, this);

	objects.push_back(newReward);
	newReward->setItList(objects.end());
}

void Game::shoot(Arrow* arrow) //Añade la flecha al array de flechas lanzadas y resta uno a las flechas disponibles
{
	shotArrows.push_back(arrow);
	objects.push_back(shotArrows.back());
	availableArrows--;
	cout << "\n Arrows: " << availableArrows;
}

int Game::getAvailableArrows() //Devuelve el numero de flechas disponibles
{
	return availableArrows;
}

Arrow* Game::collision(ArrowsGameObject* object, int cols, int rows) //Calcula la colision entre flechas y globos para todas la flechas lanzadas
{
	for (uint i = 0; i < shotArrows.size(); i++) 
	{
		if (SDL_HasIntersection(object->getCollisionRect(cols,rows), shotArrows[i]->returnPointRect())) 
		{
			return shotArrows[i];
		}
	}

	return nullptr;
}

void Game::changeScore(int value)
{
	points += value;
	cout << "\n Points: " << points;
}

void Game::update() //Llama a los update de los elementos del juego, si estos devuelven false se elimina el elemento correspondiente
{
	list<GameObject*>::iterator it;
	it = objects.begin();

	while (it != objects.end())
	{
		(*it)->update();
		++it;
	}

	it = *objectsToErase.begin();

	while (it != *objectsToErase.end())
	{
		delete *it;
		objects.remove(*it);
		++it;
	}

	objectsToErase.clear();
}

void Game::killObject(list<GameObject*>::iterator object)
{
	objectsToErase.push_back(object);
}

Game::~Game() //Destructor del juego
{
	for (GameObject* ob : objects) 
	{
		delete ob;
		objects.remove(ob);
	}

	for (uint i = 0; i < NUM_TEXTURES; i++) delete textures[i];
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
