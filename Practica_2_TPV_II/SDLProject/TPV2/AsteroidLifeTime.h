#pragma once

#include <SDL_stdinc.h> // for Uint32
#include "Component.h"

struct AsteroidLifeTime: Component {
	AsteroidLifeTime() :
			//creatiomTime_(0), //
			lifeTime_(0) //
	{
	}

	//Uint32 creatiomTime_;
	Uint32 lifeTime_;
};
