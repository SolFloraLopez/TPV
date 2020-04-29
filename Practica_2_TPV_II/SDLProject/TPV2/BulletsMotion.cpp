#include "BulletsMotion.h"
#include "Entity.h"

BulletsMotion::BulletsMotion() :
	Component(ecs::BulletsMotion) {
}

BulletsMotion::~BulletsMotion() {
}

void BulletsMotion::init() {
	pool_ = GETCMP1_(BulletsPool);
}

void BulletsMotion::update() {

	for (int i = 0; i < pool_->getPool().size(); i++)
	{
		if (pool_->getPool()[i]->inUse_)
		{
			Vector2D v = pool_->getPool()[i]->pos_ + pool_->getPool()[i]->vel_;

			if (v.getX() < 0 || v.getX() > game_->getWindowWidth() || v.getY() < 0 || v.getY() > game_->getWindowHeight()) 
				pool_->getPool()[i]->inUse_ = false;

			pool_->getPool()[i]->pos_ = v;
		}
	}
}

