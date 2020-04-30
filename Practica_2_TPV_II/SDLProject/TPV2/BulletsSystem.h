#pragma once
#include "System.h"
#include "Entity.h"
#include <cmath>
#include "SDL_macros.h"
#include "AsteroidLifeTime.h"
#include "System.h"
#include "Transform.h"
#include "Entity.h"
#include "Manager.h"
#include "BulletsPool.h"
#include "SDLGame.h"

class BulletsSystem : public System {
public:
	// - a�adir una bala al juego, como en la pr�ctica 1 pero usando entidades.
	// - no olvidar a�adir la bala al grupo _grp_Bullet
	void shoot(Vector2D pos, Vector2D vel, double width, double height) {

		Entity* b = mngr_->addEntity<BulletsPool>(pos, vel, width, height);
		if (b != nullptr)
			b->addToGroup<_grp_Bullet>();
	
	};
		// - desactivar la bala �b�
	void onCollisionWithAsteroid(Entity* b, Entity* a) {
		b->setActive(false);
	};
		// - si el juego est� parado no hacer nada.
		// - mover las balas y desactivar las que se salen de la ventana
	void update() override {};
};
