#pragma once

#include <SDL_rect.h>
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"

class BulletsViewer : public Component {
public:
	BulletsViewer();
	virtual ~BulletsViewer();
	void init() override;
	void draw() override;
private:
	Transform* tr_;
	Texture* tex_;
};