#pragma once

#include <SDL_rect.h>
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"
#include "Resources.h"


class FighterViewer : public Component {
public:
	FighterViewer();
	virtual ~FighterViewer();
	void init() override;
	void draw() override;
	void setTexture(Resources::TextureId tex) { tex_ = game_->getTextureMngr()->getTexture(tex); };

private:
	Transform* tr_;
	Texture* tex_;
	SDL_Rect* clip_;
};