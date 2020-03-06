#pragma once

#include <SDL_rect.h>
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"

class AsteroidsViewer : public Component {
public:
	AsteroidsViewer();
	virtual ~AsteroidsViewer();
	void init() override;
	void draw() override;
private:
	Transform* tr_;
	Texture* tex_;
};