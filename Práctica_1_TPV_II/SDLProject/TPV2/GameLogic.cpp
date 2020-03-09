#include "GameLogic.h"
#include "Collisions.h"
#include "Resources.h"
#include "Entity.h"

GameLogic::GameLogic(Transform *fighterTR, AsteroidPool* asteroidPool, BulletsPool* bulletsPool, Health* health) :
		Component(ecs::GameLogic), //
		fighterTR_(fighterTR), //
		asteroidPool_(asteroidPool), //
		bulletsPool_(bulletsPool), //
		health_(health), //
		scoreManager_(nullptr) //
{
}

GameLogic::~GameLogic() {
}

void GameLogic::init() {
	// scoreManager_ = GETCMP2(ecs::ScoreManager,ScoreManager);
	scoreManager_ = GETCMP1_(ScoreManager);
}

void GameLogic::update() {

	// check for collision of ball with paddles

	int i = 0; int j = 0;
	bool collided = false;

	while(i < asteroidPool_->getNumOfAsteroid() && !collided)
	{
		if (Collisions::collides(fighterTR_->getPos(), fighterTR_->getW(),
			fighterTR_->getH(), asteroidPool_->getPool()[i]->pos_, asteroidPool_->getPool()[i]->width_,
			asteroidPool_->getPool()[i]->height_))
		{
			asteroidPool_->disablAll();
			bulletsPool_->disablAll();
			scoreManager_->setStopped(true);
			if (health_->getHealth() <= 0) scoreManager_->setFinished(true);
			fighterTR_->setPos({ 0, 0 });
			fighterTR_->setRot(0);
		}
			
		else while (j < bulletsPool_->getPool().size)
		{
			if (bulletsPool_->getPool()[i]->inUse_ && Collisions::collides(bulletsPool_->getPool()[i]->pos_,
					bulletsPool_->getPool()[i]->width_, bulletsPool_->getPool()[i]->height_, asteroidPool_->getPool()[i]->pos_,
					asteroidPool_->getPool()[i]->width_, asteroidPool_->getPool()[i]->height_))
			{

			}

			j++;
		}

		i++;
	}
}

