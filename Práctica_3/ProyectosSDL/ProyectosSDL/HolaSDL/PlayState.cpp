#include "PlayState.h"

PlayState::PlayState(list<GameObject*> objects, list<EventHandler*> events, Game* game) : 
GameState(objects, events, game) {}

void PlayState::update()
{

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

			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) PlayState::exit();

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

void PlayState::rewardspawner(Point2D rewardPosition, Arrow* arrow)
{
	Reward* newReward = new Reward({ rewardPosition.getX() + 20, rewardPosition.getY() + 20 }, { 0, 1 },
		(double)352, (double)238, true, rand() % 2, textures[RewardTexture], textures[BubbleTexture], arrow, game, 2);

	newReward->setItList(objects.insert(objects.end(), newReward));
	events.push_back(newReward);
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