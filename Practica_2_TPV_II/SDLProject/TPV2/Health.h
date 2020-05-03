#pragma once

#include <SDL_rect.h>
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"

class Health : public Component
{
public:
	Health(int maxHealth): maxHealth_(maxHealth), currentHealth_(maxHealth) {
		destRect_ = RECT(0, 0, 50, 50);
	};

	void init() override {
		tex_ = game_->getTextureMngr()->getTexture(Resources::Heart);
	};
	void draw() override {
		for (int i = 0; i < currentHealth_; i++)
		{
			tex_->render(game_->getRenderer(), destRect_);
			destRect_.x += destRect_.w;
		}

		destRect_.x = 0;
	};

	void loseLife() {currentHealth_--;};
	void resetHealth() {currentHealth_ = maxHealth_;};
	int getHealth() {return currentHealth_;};
private:
	SDL_Rect  destRect_;
	Texture* tex_;
	int currentHealth_;
	int maxHealth_;
};