#include "PlayState.h"

PlayState::PlayState(list<GameObject*> objects, list<EventHandler*> events, SDLApplication* game) : 
GameState(game) {}

void PlayState::update()
{
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
		butterflySpawner();
	}

	if (!objectsToErase.empty())
	{
		it = *objectsToErase.begin();

		for (int i = 0; i < objectsToErase.size(); i++)
		{
			aux = *it;
			if (dynamic_cast<EventHandler*>(aux) != nullptr) events.remove(dynamic_cast<EventHandler*>(aux));
			it = objects.erase(it);
			delete aux;
		}

		objectsToErase.clear();
	}

	if (currentButterflies <= 0) GameState::exitGame();
}

void PlayState::render()
{
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

			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) PlayState::getExit();

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
	}
}

Arrow* PlayState::collision(ArrowsGameObject* object, int cols, int rows)
{
	for (uint i = 0; i < shotArrows.size(); i++)
	{
		if (SDL_HasIntersection(object->getCollisionRect(cols, rows), shotArrows[i]->returnPointRect()))
		{
			return shotArrows[i];
		}
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
			(double)597, { -1, 2 + (rand() % 4) * BALLOON_VELOCITY }, true, GameState::getTexture(Balloons), rand() % 7, game, 3);

		newBalloon->setItList(objects.insert(objects.end(), newBalloon));
	}
};

void PlayState::rewardspawner(Point2D rewardPosition, Arrow* arrow)
{
	Reward* newReward = new Reward({ rewardPosition.getX() + 20, rewardPosition.getY() + 20 }, { 0, 1 },
		(double)352, (double)238, true, rand() % 2, GameState::getTexture(RewardTexture), GameState::getTexture(BubbleTexture), arrow, game, 2);

	newReward->setItList(objects.insert(objects.end(), newReward));
	events.push_back(newReward);
}

void PlayState::butterflySpawner()
{
	currentButterflies = BASE_BUTTERFLY_AMOUNT * ((currentMap % MAP_AMOUNT) + 1);//

	for (int i = 0; i < currentButterflies; i++)
	{
		Butterfly* newButterfly = new Butterfly({ ((double)WIN_WIDTH / 3) + rand() % (WIN_WIDTH / 3), (double)(rand() % (WIN_HEIGHT - 92)) },
			{ 1 - (double)(rand() % 2) * 2 , 1 - (double)(rand() % 2) * 2 }, (double)384, (double)368, true, GameState::getTexture(ButterflyTexture), game, 1);

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

void PlayState::saveToFile(string file)
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

	output.close();
}