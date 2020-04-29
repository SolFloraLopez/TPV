#include "AsteroidsMotion.h"
#include "Entity.h"

AsteroidsMotion::AsteroidsMotion() :
	Component(ecs::AsteroidsMotion){
}

AsteroidsMotion::~AsteroidsMotion() {
}

void AsteroidsMotion::init() 
{
	pool_ = GETCMP1_(AsteroidPool);
}

void AsteroidsMotion::update() {

	
	for (int i = 0; i < pool_->getPool().size(); i++)
	{
		if (pool_->getPool()[i]->inUse_)
		{
			Vector2D v = pool_->getPool()[i]->pos_ + pool_->getPool()[i]->vel_;

			if (v.getX() < 0) v.setX(game_->getWindowWidth());
			else if (v.getX() > game_->getWindowWidth()) v.setX(0);

			if (v.getY() < 0) v.setY(game_->getWindowHeight());
			else if (v.getY() > game_->getWindowHeight()) v.setY(0);

			pool_->getPool()[i]->pos_ = v;
			pool_->getPool()[i]->rot_ = pool_->getPool()[i]->rot_ + 0.5;
		}
	}
}

