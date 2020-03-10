#pragma once

#include <SDL_rect.h>
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "AsteroidPool.h"
#include "Resources.h"

class AsteroidsViewer : public Component {
public:
	AsteroidsViewer();
	virtual ~AsteroidsViewer();
	void init() override;
	void draw() override;
	void setTexture(Resources::TextureId tex) { tex_ = game_->getTextureMngr()->getTexture(tex); };
private:
	AsteroidPool* pool_;
	Texture* tex_;
};