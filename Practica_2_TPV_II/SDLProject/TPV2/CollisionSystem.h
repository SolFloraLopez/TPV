#pragma once

#include "Collisions.h"
#include "System.h"
#include "Manager.h"
#include "StarsSystem.h"
#include "FighterSystem.h"
#include "AsteroidsSystem.h"
#include "BulletsSystem.h"
#include "Transform.h"

class CollisionSystem: public System {
public:

	// - si el juego está parado no hacer nada.
	// - comprobar colisiones usando el esquema abajo (nota las instrucciones break
	// y continue, piensa porque son necesarias).
	void update() override {
		auto gt = mngr_->getHandler<_hdlr_GameState>()->addComponent<GameState>();
		if (gt->state_ != gt->Parado)
		{
			auto ftr = mngr_->getHandler<_hdlr_Fighter>()->getComponent<Transform>();
			for (auto& a : mngr_->getGroupEntities<_grp_Asteroid>()) {
				auto atr = a->getComponent<Transform>();
				if (Collisions::collides(ftr->position_, ftr->width_, ftr->height_, atr->position_, atr->width_, atr->height_)) {
					mngr_->getSystem<FighterSystem>()->onCollisionWithAsteroid(a);
					break;
				}

				for (auto& b : mngr_->getGroupEntities<_grp_Bullet>()) {
					if (!b->isActive()) continue;
					if (!a->isActive()) break;
					auto btr = b->getComponent<Transform>();
					if (Collisions::collides(btr->position_, btr->width_, btr->height_, atr->position_, atr->width_, atr->height_)) {
						// - llamar a onCollisionWithAsteroid(...) del BulletsSystem.
						// - llamar a onCollisionWithBullet(...) del AsteroidsSystem.
						// …
						mngr_->getSystem<BulletsSystem>()->onCollisionWithAsteroid(b, a);
						mngr_->getSystem<AsteroidsSystem>()->onCollisionWithBullet(a, b);
					}
				}
			}
		}		
	}
};

