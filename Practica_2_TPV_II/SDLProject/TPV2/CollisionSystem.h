#pragma once

#include "Collisions.h"
#include "System.h"
#include "Manager.h"
#include "StarsSystem.h"
#include "Transform.h"

class CollisionSystem: public System {
public:

	// - si el juego está parado no hacer nada.
	// - comprobar colisiones usando el esquema abajo (nota las instrucciones break
	// y continue, piensa porque son necesarias).
	void update() override {
		//…
			for (auto& a : /* asteroides */) {
				//…
					if ( /* hay choque entre “a” y el caza */) {
						// - llamar a onCollisionWithAsteroid(a) del FighterSystem
						break;
					}
				for (auto& b : /* balas */) {
					if (!b->isActive()) continue;
					if (!a->isActive()) break;
					if ( /* hay choque entre ‘a’ y ‘b’ */) {
						// - llamar a onCollisionWithAsteroid(...) del BulletsSystem.
						// - llamar a onCollisionWithBullet(...) del AsteroidsSystem.
						// …
					}
				}
			}


	/*void update() {
		auto ptr = mngr_->getHandler<_hdlr_PacMan>()->getComponent<Transform>();
		for( auto& e : mngr_->getGroupEntities<_grp_Star>()) {
			auto etr = e->getComponent<Transform>();
			if ( Collisions::collides(ptr->position_, ptr->width_, ptr->height_, etr->position_, etr->width_, etr->height_)) {
				mngr_->getSystem<StarsSystem>()->onCollision(e);
			}
		}
	}*/
};

