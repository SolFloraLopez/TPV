#pragma once

#include "Collisions.h"
#include "System.h"
#include "Manager.h"
#include "FighterSystem.h"
#include "AsteroidsSystem.h"
#include "BulletsSystem.h"
#include "GameCtrlSystem.h"
#include "Transform.h"
#include "Score.h"

class CollisionSystem: public System {
public:

	// - si el juego está parado no hacer nada.
	// - comprobar colisiones usando el esquema abajo (nota las instrucciones break
	// y continue, piensa porque son necesarias).
	void update() override {
		auto gt = mngr_->getHandler<_hdlr_GameState>()->addComponent<GameState>();
		if (!gt->isStopped())
		{
			auto ftr = mngr_->getHandler<_hdlr_Fighter>()->getComponent<Transform>();
			for (auto& a : mngr_->getGroupEntities<_grp_Asteroid>()) {
				auto atr = a->getComponent<Transform>();
				if (Collisions::collides(ftr->position_, ftr->width_, ftr->height_, atr->position_, atr->width_, atr->height_)) {
					mngr_->getSystem<FighterSystem>()->onCollisionWithAsteroid(a);
					game_->getAudioMngr()->haltMusic();
					game_->getAudioMngr()->playChannel(Resources::Explosion, 0);

					mngr_->getHandler<_hdlr_Fighter>()->getComponent<Health>()->loseLife();

					if (mngr_->getHandler<_hdlr_Fighter>()->getComponent<Health>()->getHealth() <= 0) {
						mngr_->getSystem<GameCtrlSystem>()->onFighterDeath();
					}

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
						game_->getAudioMngr()->playChannel(Resources::Explosion, 0);
						mngr_->getHandler<_hdlr_GameState>()->addComponent<Score>()->points_++;
						mngr_->getSystem<BulletsSystem>()->onCollisionWithAsteroid(b, a);
						mngr_->getSystem<AsteroidsSystem>()->onCollisionWithBullet(a, b);

						if (mngr_->getSystem<AsteroidsSystem>()->getNumAsteroids() <= 0) {
							mngr_->getSystem<GameCtrlSystem>()->onAsteroidsExtenction();
						}

					}
				}
			}
		}		
	}
};

