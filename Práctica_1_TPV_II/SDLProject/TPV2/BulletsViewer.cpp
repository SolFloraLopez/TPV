#include "BulletsViewer.h"

BulletsViewer::BulletsViewer() : Component(ecs::BulletsViewer) {}

BulletsViewer::~BulletsViewer() {}

void BulletsViewer::init()
{
	pool_ = GETCMP1_(BulletsPool);
	tex_ = game_->getTextureMngr()->getTexture(Resources::Bullets);
}

void BulletsViewer::draw()
{
	for (int i = 0; i < pool_->getPool().size(); i++)
	{
		if (pool_->getPool()[i]->inUse_)
		{
			SDL_Rect rect
				RECT(pool_->getPool()[i]->pos_.getX(), pool_->getPool()[i]->pos_.getY(), pool_->getPool()[i]->width_,
					pool_->getPool()[i]->height_);

			tex_->render(game_->getRenderer(), rect, pool_->getPool()[i]->rot_);
		}
	}
}