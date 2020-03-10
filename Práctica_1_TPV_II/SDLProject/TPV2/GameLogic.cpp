#include "GameLogic.h"
#include "Collisions.h"
#include "Resources.h"
#include <iostream>

#include "Entity.h"

GameLogic::GameLogic(Transform* fighterTR, AsteroidPool* asteroidPool, BulletsPool* bulletsPool, Health* health) :
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

		
		while (i < asteroidPool_->getNumOfAsteroid() && !collided)
		{
			if (Collisions::collidesWithRotation(fighterTR_->getPos(), fighterTR_->getW(),
				fighterTR_->getH(),fighterTR_->getRot(), asteroidPool_->getPool()[i]->pos_, asteroidPool_->getPool()[i]->width_,
				asteroidPool_->getPool()[i]->height_, asteroidPool_->getPool()[i]->rot_))
			{
				asteroidPool_->disablAll();
				bulletsPool_->disablAll();
				scoreManager_->setStopped(true);
				health_->loseLife();

				if (health_->getHealth() <= 0) {
					scoreManager_->setFinished(true);
				}

				fighterTR_->setPos({ game_->getWindowWidth() / 2.0, game_->getWindowHeight() / 2.0 });				
				fighterTR_->setRot(0);
				fighterTR_->setVel(0.0, 0.0);

				collided = true;
			}

			
			else while (j < bulletsPool_->getPool().size())
			{
				if (bulletsPool_->getPool()[j]->inUse_ && Collisions::collidesWithRotation(bulletsPool_->getPool()[j]->pos_,
					bulletsPool_->getPool()[j]->width_, bulletsPool_->getPool()[j]->height_, bulletsPool_->getPool()[j]->rot_, asteroidPool_->getPool()[i]->pos_,
					asteroidPool_->getPool()[i]->width_, asteroidPool_->getPool()[i]->height_, asteroidPool_->getPool()[i]->rot_))
				{
					scoreManager_->setScore(scoreManager_->getScore() + 1);
					bulletsPool_->onCollision(bulletsPool_->getPool()[j]);
					asteroidPool_->onCollision(asteroidPool_->getPool()[i]);
					

					if (asteroidPool_->getNumOfAsteroid() <= 0) {
						fighterTR_->setPos({ game_->getWindowWidth() / 2.0, game_->getWindowHeight()/2.0 });
						fighterTR_->setRot(0);
						fighterTR_->setVel(0.0, 0.0);
						scoreManager_->setFinished(true);
					}
				}

				j++;
			}

			j = 0;

			i++;
		}

		collided = false;
	
}

