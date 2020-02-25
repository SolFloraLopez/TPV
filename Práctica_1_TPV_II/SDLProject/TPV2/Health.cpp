#include "Health.h"

Health::Health(): Component(ecs::Health) 
{
	destRect_ = RECT(0, 0, 50, 50);
}

Health::~Health(){}

void Health::init()
{
	tex_ = game_->getTextureMngr()->getTexture(Resources::Heart);
}

void Health::draw()
{
	tex_->render(game_->getRenderer(), destRect_);
}