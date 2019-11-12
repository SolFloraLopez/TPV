#pragma once
#include "Vector2D.h"
#include "Texture.h"

class GameObject {
public:
	virtual ~GameObject();
	virtual void render() = 0{}
	virtual bool update() = 0{}
};