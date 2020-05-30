#pragma once

#include <SDL_rect.h>
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"

class Health : public Component
{
public:
	Health(int maxHealth): maxHealth_(maxHealth), currentHealth_(maxHealth) 
	{
	};
	Health() {};

	
	void loseLife() {currentHealth_--;};
	void resetHealth() {currentHealth_ = maxHealth_;};
	int getHealth() {return currentHealth_;};
private:
	int currentHealth_;
	int maxHealth_;
};