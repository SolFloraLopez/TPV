#pragma once

#include <SDL_rect.h>
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"

class Health : public Component
{
public:
	Health(int maxHealth);
	virtual ~Health();
	void init() override;
	void draw() override;
	void loseLife();
	void resetHealth();
private:
	SDL_Rect  destRect_;
	Texture* tex_;
	int currentHealth_;
	int maxHealth_;
};