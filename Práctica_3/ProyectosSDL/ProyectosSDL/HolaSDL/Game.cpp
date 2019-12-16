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

Game::Game(bool load, string route) 
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

	if (!load) {
		Bow* bow = new Bow({ 0,0 }, BOW_HEIGHT, BOW_WIDTH,
			{ 0, BOW_VELOCITY }, textures[BowTexture], textures[ArrowTexture], true, this, 0); //Crea el arco

		objects.push_back(bow);
		events.push_back(bow);
		bow->setItList(objects.end());

		butterflyspawner();
	}
	else {
		loadFromFile(route);
	}
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

	list<GameObject*>::iterator it;//

	it = objects.begin();

	while (it != objects.end())
	{
		(*it)->render();
		++it;
	}//
	
	SDL_RenderPresent(renderer);
};

void Game::handleEvents() //Llama a HandleEvents del bow mientras que exit sea false, mientras que el jugador no salga del juego
{

	SDL_Event event;//

	if (!events.empty())
	{
		while (SDL_PollEvent(&event) && !exit) {

			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) exit = true;

			if (!recordingInput && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
			{
				recordingInput = true;
			}

			if (recordingInput && event.type == SDL_KEYDOWN && event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9)
			{
				file += event.key.keysym.sym;
			}

			else if (recordingInput && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
			{
				recordingInput = false;
				saving = true;
			}

			list<EventHandler*>::iterator eh;

			eh = events.begin();

			while (eh != events.end())
			{
				(*eh)->handleEvent(event);
				++eh;
			}
		}
	}//
}

void Game::balloonspawner() //Generador de globos
{
	if (rand() % 20 == 1)
	{
		Balloon* newBalloon = new Balloon({ ((double)WIN_WIDTH / 2) + rand() % (WIN_WIDTH / 2), WIN_HEIGHT }, (double)512,
			(double)597, { -1, 2 + (rand() % 4) * BALLOON_VELOCITY }, true, textures[Balloons], rand() % 7, this, 3);

		newBalloon->setItList(objects.insert(objects.end(), newBalloon));
	}
};

void Game::butterflyspawner() //Generador de mariposas
{
	currentButterflies = BASE_BUTTERFLY_AMOUNT * ((currentMap % MAP_AMOUNT) + 1);//

	for (int i = 0; i < currentButterflies; i++)
	{
		Butterfly* newButterfly = new Butterfly({ ((double)WIN_WIDTH / 3) + rand() % (WIN_WIDTH / 3), (double)(rand() % (WIN_HEIGHT - 92)) },
			{ 1 - (double)(rand() % 2) * 2 , 1 - (double)(rand() % 2) * 2 }, (double)384, (double)368, true, textures[ButterflyTexture], this, 1);

		newButterfly->setItList(objects.insert(objects.end(), newButterfly));//
	}
};

void Game::rewardspawner(Point2D rewardPosition, Arrow* arrow)
{
	Reward* newReward = new Reward({ rewardPosition.getX() + 20, rewardPosition.getY() + 20}, { 0, 1 },//
		(double)352, (double)238, true, rand() % 2, textures[RewardTexture], textures[BubbleTexture], arrow, this, 2);

	newReward->setItList(objects.insert(objects.end(), newReward));
	events.push_back(newReward);//
}

void Game::shoot(Arrow* arrow) //Añade la flecha al array de flechas lanzadas y resta uno a las flechas disponibles
{
	shotArrows.push_back(arrow); //
	arrow->setItList(objects.insert(objects.end(), arrow));
	availableArrows--;
	changeCurrentArrows(1); //
}

int Game::changeAvaliableArrows(int amount)
{
	availableArrows += amount;//
	return availableArrows;//
}

int Game::changeCurrentArrows(int amount)
{
	currentArrows += amount; //
	return currentArrows;//
}

Arrow* Game::collision(ArrowsGameObject* object, int cols, int rows) //Calcula la colision entre flechas y globos para todas la flechas lanzadas
{
	for (uint i = 0; i < shotArrows.size(); i++) //
	{
		if (SDL_HasIntersection(object->getCollisionRect(cols,rows), shotArrows[i]->returnPointRect())) 
		{
			return shotArrows[i];
		}
	}

	return nullptr;//
}

int Game::changeScore(int value)
{
	points += value;//
	if (points < 0) points = 0;
	return points;//
}

void Game::updateButterflyCounter()
{
	currentButterflies--;//
}

void Game::update() //Llama a los update de los elementos del juego, si estos devuelven false se elimina el elemento correspondiente
{
	if (saving) {//
		saveToFile();
	}

	list<GameObject*>::iterator it;
	GameObject* aux;

	it = objects.begin();

	while (it != objects.end())
	{
		(*it)->update();
		++it;
	}

	if (points >= currentMaxPoints)
	{
		it = next(objects.begin(), 2);
		int j = objects.size();

		for (int i = 2; i < j; i++)
		{
			aux = *it;
			if (dynamic_cast<EventHandler*>(aux) != nullptr) events.remove(dynamic_cast<EventHandler*>(aux));
			it = objects.erase(it);
			delete aux;
		}

		currentMap++;
		currentMaxPoints += BASE_POINT_MAX * ((currentMap % MAP_AMOUNT) + 1);
		availableArrows = BASE_ARROWS_AMOUNT * ((currentMap % MAP_AMOUNT) + 1);
		butterflyspawner();
	}

	if(!objectsToErase.empty()) 
	{
		it = *objectsToErase.begin();

		for(int i = 0; i < objectsToErase.size(); i++)
		{
			aux = *it;
			if (dynamic_cast<EventHandler*>(aux) != nullptr) events.remove(dynamic_cast<EventHandler*>(aux));
			it = objects.erase(it);
			delete aux;
		}

		objectsToErase.clear();
	}

	if (currentButterflies <= 0) exit = true;//
}

void Game::killObject(list<GameObject*>::iterator object)
{
	objectsToErase.push_back(object); //
}

bool Game::getSaving()
{
	return saving;
}

bool Game::getExit()
{
	return exit;
}

void Game::exitGame()
{
	exit = true;
}

void Game::saveToFile()//
{
	ofstream output(file);

	output << availableArrows << " " << currentButterflies << " " << currentArrows << " " 
		<< points << " " << currentMap << " " << currentMaxPoints << " " << objects.size() << "\n";

	list<GameObject*>::iterator it;

	it = objects.begin();

	while (it != objects.end())
	{
		(*it)->saveToFile(output);
		++it;

		output << "\n";
	}

	output.close();//
}

void Game::loadFromFile(string route)
{
	fstream input(route);

	input >> availableArrows; input >> currentButterflies; input >> currentArrows; input >> points;
	input >> currentMap; input >> currentMaxPoints;

	ScoreBoard* scoreBoard = new ScoreBoard(textures[DigitsTexture], textures[ScoreArrowTexture], this);
	objects.push_back(scoreBoard);
	scoreBoard->setItList(objects.end());

	int size, aux;
	input >> size;

	for(int i = 0; i < size; i++)
	{
		input >> aux;
		switch (aux)
		{
		case 0:
		{Bow* bow = new Bow({ 0,0 }, BOW_HEIGHT, BOW_WIDTH,
			{ 0, BOW_VELOCITY }, textures[BowTexture], textures[ArrowTexture], true, this, 0); //Crea el arco

		objects.push_back(bow);
		events.push_back(bow);
		bow->setItList(objects.end());
		bow->loadFromFile(input);
		break; }
		case 1:
		{Butterfly* newButterfly = new Butterfly({ 0, 0 }, { 0, 0 }, (double)0, (double)0, true, textures[ButterflyTexture], this, 1);
		newButterfly->setItList(objects.insert(objects.end(), newButterfly));
		newButterfly->loadFromFile(input);
		break; }
		case 2:
		{Reward* newReward = new Reward({ 0, 0 }, { 0, 0 },
			(double)0, (double)0, true, 0, textures[RewardTexture], textures[BubbleTexture], nullptr, this, 2);
		newReward->setItList(objects.insert(objects.end(), newReward));
		events.push_back(newReward);
		newReward->loadFromFile(input);
		break; }
		case 3:
		{Balloon* newBalloon = new Balloon({ 0, 0 }, (double)0, (double)0, { 0, 0 }, true, textures[Balloons], 0, this, 3);
		newBalloon->setItList(objects.insert(objects.end(), newBalloon));
		newBalloon->loadFromFile(input);
		break; }
		case 4:
		{Arrow* arrow = new Arrow(0, 0, { 0, 0 }, { 0, 0 }, textures[ArrowTexture], this, 4);
		shotArrows.push_back(arrow);
		arrow->setItList(objects.insert(objects.end(), arrow));
		arrow->loadFromFile(input);
		break; }
		default:
			break;
		}
	}

	input.close();
}

void Game::newSaveToFile()
{
	stateMachine->popState();
	cin >> file;
	stateMachine->currentState()->saveToFile(file);
	stateMachine->pushState(new PauseState(this));
}

Texture* Game::getTexture(int num)
{
	return textures[num];
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
