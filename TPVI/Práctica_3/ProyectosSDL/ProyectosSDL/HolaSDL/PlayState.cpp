#include "PlayState.h"

PlayState::PlayState(SDLApplication* game, bool load, string file) :
GameState(game)
{
	ScoreBoard* scoreBoard = new ScoreBoard(getTexture(DigitsTexture), getTexture(ScoreArrowTexture), this);
	objects.push_back(scoreBoard);
	scoreBoard->setItList(objects.end());

	if (!load) {
		Bow* bow = new Bow({ 0,0 }, BOW_HEIGHT, BOW_WIDTH,{ 0, BOW_VELOCITY }, 
			getTexture(BowTexture), getTexture(ArrowTexture), true, this, 0); //Crea el arco

		objects.push_back(bow);
		events.push_back(bow);
		bow->setItList(objects.end());
		butterflySpawner();
	}

	else loadFromFile(file);
}

void PlayState::update()
{
	balloonspawner();

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
		currentArrows = 0;
		butterflySpawner();
	}

	if (!objectsToErase.empty())
	{
		it = *objectsToErase.begin();

		for (int i = 0; i < objectsToErase.size(); i++)
		{
			aux = *it;
			if (dynamic_cast<EventHandler*>(aux) != nullptr) events.remove(dynamic_cast<EventHandler*>(aux));
			if (dynamic_cast<Arrow*>(aux) != nullptr) shotArrows.remove(dynamic_cast<Arrow*>(aux));
			it = objects.erase(it);
			delete aux;
		}

		objectsToErase.clear();
	}

	if (currentButterflies <= 0) GameState::End();
}

void PlayState::render()
{
	getTexture(currentMap % MAP_AMOUNT)->render({ 0, 0, WIN_WIDTH, WIN_HEIGHT });

	list<GameObject*>::iterator it;

	it = objects.begin();

	while (it != objects.end())
	{
		(*it)->render();
		++it;
	}
}

void PlayState::handleEvents()
{
	SDL_Event event;

	if (!events.empty())
	{
		while (SDL_PollEvent(&event) && !PlayState::getExit()) {

			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) GameState::Pause();

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

Arrow* PlayState::collision(ArrowsGameObject* object, int cols, int rows)
{
	list<Arrow*>::iterator it;

	it = shotArrows.begin();

	while (it != shotArrows.end())
	{
		if (SDL_HasIntersection(object->getCollisionRect(cols, rows), (*it)->returnPointRect()))
		{
			return *it;
		}
		++it;
	}

	return nullptr;
}

void PlayState::shoot(Arrow* arrow)
{
	shotArrows.push_back(arrow);
	arrow->setItList(objects.insert(objects.end(), arrow));
	availableArrows--;
	changeCurrentArrows(1);
}

int PlayState::changeScore(int value)
{
	points += value;
	if (points < 0) points = 0;
	return points;
}

void PlayState::balloonspawner() //Generador de globos
{
	if (rand() % 20 == 1)
	{
		Balloon* newBalloon = new Balloon({ ((double)WIN_WIDTH / 2) + rand() % (WIN_WIDTH / 2), WIN_HEIGHT }, (double)512,
			(double)597, { -1, 2 + (rand() % 4) * BALLOON_VELOCITY }, true, GameState::getTexture(Balloons), rand() % 7, this, 3);

		newBalloon->setItList(objects.insert(objects.end(), newBalloon));
	}
};

void PlayState::rewardspawner(Point2D rewardPosition, Arrow* arrow)
{
	Reward* newReward = new Reward({ rewardPosition.getX() + 20, rewardPosition.getY() + 20 }, { 0, 1 },
		(double)352, (double)238, true, rand() % 2, GameState::getTexture(RewardTexture), GameState::getTexture(BubbleTexture), arrow, this, 2);

	newReward->setItList(objects.insert(objects.end(), newReward));
	events.push_back(newReward);
}

void PlayState::butterflySpawner()
{
	currentButterflies = BASE_BUTTERFLY_AMOUNT * ((currentMap % MAP_AMOUNT) + 1);//

	for (int i = 0; i < currentButterflies; i++)
	{
		Butterfly* newButterfly = new Butterfly({ ((double)WIN_WIDTH / 3) + rand() % (WIN_WIDTH / 3), (double)(rand() % (WIN_HEIGHT - 92)) },
			{ 1 - (double)(rand() % 2) * 2 , 1 - (double)(rand() % 2) * 2 }, (double)384, (double)368, true, GameState::getTexture(ButterflyTexture), this, 1);

		newButterfly->setItList(objects.insert(objects.end(), newButterfly));//
	}
}

void PlayState::killObject(list<GameObject*>::iterator object)
{
	objectsToErase.push_back(object);
}

void PlayState::updateButterflyCounter()
{
	currentButterflies--;
}

int PlayState::changeAvaliableArrows(int amount)
{
	availableArrows += amount;
	return availableArrows;
}

int PlayState::changeCurrentArrows(int amount)
{
	currentArrows += amount;
	return currentArrows;
}

void PlayState::saveToFile()
{
	string file;
	cout << "Introduzca el codigo para el archivo de guardado: ";
	cin >> file;

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

	output.close();

	cout << "Archivo guardado";
}

void PlayState::loadFromFile(string file)
{
	fstream input(file);

	if (!input.is_open()) throw FileNotFoundError(file);

	input >> availableArrows; input >> currentButterflies; input >> currentArrows; input >> points;
	input >> currentMap; input >> currentMaxPoints;

	int size, aux;
	input >> size;

	try
	{
		for (int i = 0; i < size; i++)
		{
			input >> aux;
			switch (aux)
			{
			case 0:
			{Bow* bow = new Bow({ 0,0 }, BOW_HEIGHT, BOW_WIDTH,
				{ 0, BOW_VELOCITY }, getTexture(BowTexture), getTexture(ArrowTexture), true, this, 0); //Crea el arco

			objects.push_back(bow);
			events.push_back(bow);
			bow->setItList(objects.end());
			bow->loadFromFile(input);
			break; }
			case 1:
			{Butterfly* newButterfly = new Butterfly({ 0, 0 }, { 0, 0 }, (double)0, (double)0, true, getTexture(ButterflyTexture), this, 1);
			newButterfly->setItList(objects.insert(objects.end(), newButterfly));
			newButterfly->loadFromFile(input);
			break; }
			case 2:
			{Reward* newReward = new Reward({ 0, 0 }, { 0, 0 },
				(double)0, (double)0, true, 0, getTexture(RewardTexture), getTexture(BubbleTexture), nullptr, this, 2);
			newReward->setItList(objects.insert(objects.end(), newReward));
			events.push_back(newReward);
			newReward->loadFromFile(input);
			break; }
			case 3:
			{Balloon* newBalloon = new Balloon({ 0, 0 }, (double)0, (double)0, { 0, 0 }, true, getTexture(Balloons), 0, this, 3);
			newBalloon->setItList(objects.insert(objects.end(), newBalloon));
			newBalloon->loadFromFile(input);
			break; }
			case 4:
			{Arrow* arrow = new Arrow(0, 0, { 0, 0 }, { 0, 0 }, getTexture(ArrowTexture), this, 4);
			shotArrows.push_back(arrow);
			arrow->setItList(objects.insert(objects.end(), arrow));
			arrow->loadFromFile(input);
			break; }
			default:
				break;
			}
		}
	}
	catch (exception)
	{
		throw FileFormatError(file);
	}

	input.close();
}