#pragma once

#include <SDL_rect.h>
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "BulletsPool.h"
#include "Resources.h"


class BulletsViewer : public Component {
public:
	BulletsViewer();
	virtual ~BulletsViewer();
	void init() override;
	void draw() override;
	void setTexture(Resources::TextureId tex) { tex_ = game_->getTextureMngr()->getTexture(tex); };

private:
	BulletsPool* pool_;
	Texture* tex_;
};