#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include "Game.h"
#include "Texture.h"
#include <iostream>
#include <fstream>
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

	ScoreBoard* scoreBoard = new ScoreBoard(textures[DigitsTexture], textures[ScoreArrowTexture], this);
	objects.push_back(scoreBoard);
	scoreBoard->setItList(objects.end());

	Bow* bow = new Bow({ 0,0 }, (double)82, (double)190,
	{ 0, BOW_VELOCITY }, textures[BowTexture], textures[ArrowTexture], true, this); //Crea el arco

	objects.push_back(bow);
	events.push_back(bow);
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
	textures[currentMap % MAP_AMOUNT]->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });

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

	if (!events.empty())
	{
		while (SDL_PollEvent(&event) && !exit) {
			if (event.type == SDL_QUIT) exit = true;
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s) saveToFile(435);

			list<EventHandler*>::iterator eh;

			eh = events.begin();

			while (eh != events.end())
			{
				(*eh)->handleEvent(event);
				++eh;
			}
		}
	}
}

void Game::balloonspawner() //Generador de globos
{
	if (rand() % 20 == 1)
	{
		Balloon* newBalloon = new Balloon({ ((double)WIN_WIDTH / 2) + rand() % (WIN_WIDTH / 2), WIN_HEIGHT }, (double)512,
			(double)597, { -1, 2 + (rand() % 4) * BALLOON_VELOCITY }, true, textures[Balloons], rand() % 7, this);

		newBalloon->setItList(objects.insert(objects.end(), newBalloon));
	}
};

void Game::butterflyspawner() //Generador de mariposas
{

	int newButterflies = BASE_BUTTERFLY_AMOUNT * ((currentMap % MAP_AMOUNT) + 1) - currentButterflies;

	for (int i = 0; i < newButterflies; i++)
	{
		Butterfly* newButterfly = new Butterfly({ ((double)WIN_WIDTH / 3) + rand() % (WIN_WIDTH / 3), (double)(rand() % (WIN_HEIGHT - 92)) },
			{ 1 - (double)(rand() % 2) * 2 , 1 - (double)(rand() % 2) * 2 }, (double)384, (double)368, true, textures[ButterflyTexture], this);

		newButterfly->setItList(objects.insert(objects.end(), newButterfly));
		currentButterflies++;
	}
};

void Game::rewardspawner(Point2D rewardPosition, Arrow* arrow)
{
	Reward* newReward = new Reward({ rewardPosition.getX() + 20, rewardPosition.getY() + 20}, { 0, 1 },
		(double)352, (double)238, true, rand() % 2, textures[RewardTexture], textures[BubbleTexture], arrow, this);

	newReward->setItList(objects.insert(objects.end(), newReward));
	events.push_back(newReward);
}

void Game::shoot(Arrow* arrow) //Añade la flecha al array de flechas lanzadas y resta uno a las flechas disponibles
{
	shotArrows.push_back(arrow);
	arrow->setItList(objects.insert(objects.end(), arrow));
	availableArrows--;
	changeCurrentArrows(1);
}

int Game::changeAvaliableArrows(int amount)
{
	availableArrows += amount;
	return availableArrows;
}

int Game::changeCurrentArrows(int amount)
{
	currentArrows += amount;
	return currentArrows;
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

int Game::changeScore(int value)
{
	points += value;
	cout << "\n Points: " << points;
	return points;
}

void Game::updateButterflyCounter()
{
	currentButterflies--;
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

	if(!objectsToErase.empty()) 
	{
		it = *objectsToErase.begin();
		GameObject* aux;

		for(int i = 0; i < objectsToErase.size(); i++)
		{
			aux = *it;
			if (dynamic_cast<EventHandler*>(aux) != nullptr) events.remove(dynamic_cast<EventHandler*>(aux));
			it = objects.erase(it);
			delete aux;
		}

		objectsToErase.clear();
	}

	if (currentButterflies <= 0) exit = true;

	if (points >= currentMaxPoints)
	{
		currentMap++;
		currentMaxPoints += BASE_POINT_MAX * (currentMap % MAP_AMOUNT);
		availableArrows = BASE_ARROWS_AMOUNT * ((currentMap % MAP_AMOUNT) + 1);
		butterflyspawner();
	}
}

void Game::killObject(list<GameObject*>::iterator object)
{
	objectsToErase.push_back(object);
}

void Game::exitGame()
{
	exit = true;
}

void Game::saveToFile(int fileNumber)
{
	ofstream output("Bazinga");

	output << availableArrows << " " << currentButterflies << " " << currentArrows
		<< " " << points << " " << currentMap << " " << currentMaxPoints << "\n";

	output.close();
}

Game::~Game() //Destructor del juego
{
	for (GameObject* ob : objects) 
	{
		delete ob;
	}

	for (uint i = 0; i < NUM_TEXTURES; i++) delete textures[i];
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
