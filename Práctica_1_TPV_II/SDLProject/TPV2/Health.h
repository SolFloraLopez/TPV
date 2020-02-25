#pragma once

#include <SDL_rect.h>
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"

class Health : public Component
{
public:
	Health();
	virtual ~Health();
	void init() override;
	void draw() override;
private:
	SDL_Color color_;
	SDL_Rect  destRect_;
	Texture* tex_;
};