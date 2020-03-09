#pragma once

#include <SDL_rect.h>
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "AsteroidPool.h"

class AsteroidsViewer : public Component {
public:
	AsteroidsViewer();
	virtual ~AsteroidsViewer();
	void init() override;
	void draw() override;
private:
	AsteroidPool* pool_;
	Texture* tex_;
};