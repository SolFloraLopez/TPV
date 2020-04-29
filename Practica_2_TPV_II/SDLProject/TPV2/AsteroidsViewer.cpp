#include "AsteroidsViewer.h"

AsteroidsViewer::AsteroidsViewer() : Component(ecs::AsteroidsViewer) {}

AsteroidsViewer::~AsteroidsViewer() {}

void AsteroidsViewer::init()
{
	tex_ = game_->getTextureMngr()->getTexture(Resources::Asteroids);
	pool_ = GETCMP1_(AsteroidPool);
}

void AsteroidsViewer::draw()
{
	for(int i = 0; i < pool_->getPool().size(); i++)
	{
		if(pool_->getPool()[i]->inUse_)
		{
			SDL_Rect rect
				RECT(pool_->getPool()[i]->pos_.getX(), pool_->getPool()[i]->pos_.getY(), pool_->getPool()[i]->width_,
					pool_->getPool()[i]->height_);

			tex_->render(game_->getRenderer(), rect, pool_->getPool()[i]->rot_);
		}
	}
}