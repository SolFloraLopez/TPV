#include "Health.h"

Health::Health(int maxHealth): Component(ecs::Health), maxHealth_(maxHealth), currentHealth_(maxHealth)
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
	for(int i = 0; i < currentHealth_; i++)
	{
		tex_->render(game_->getRenderer(), destRect_);
		destRect_.x += destRect_.w;
	}

	destRect_.x = 0;
}

void Health::loseLife()
{
	currentHealth_--;
}

void Health::resetHealth()
{
	currentHealth_ = maxHealth_;
}