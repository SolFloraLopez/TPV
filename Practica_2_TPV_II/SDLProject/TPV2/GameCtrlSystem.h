#pragma once

#include "ecs.h"
#include "System.h"
#include "Score.h"
#include "Health.h"
#include "GameState.h"
#include "Manager.h"
#include "AsteroidsSystem.h"


class GameCtrlSystem: public System {
public:
	// - a este método se le va a llamar cuando muere el caza.
	// - desactivar todos los asteroides y las balas.
	// - actualizar los componentes correspondientes (Score, Heath, GameState, …).
	void onFighterDeath() {
		for (auto& a : mngr_->getGroupEntities<_grp_Asteroid>()) {
			a->setActive(false);
		}
		for (auto& b : mngr_->getGroupEntities<_grp_Bullet>()) {
			b->setActive(false);
		}
		mngr_->getHandler<_hdlr_Fighter>()->getComponent<Health>()->loseLife();
		mngr_->getHandler<_hdlr_GameState>()->addComponent<Score>()->points_ = 0;
		mngr_->getHandler<_hdlr_GameState>()->addComponent<GameState>()->setFinished(true);
		mngr_->getHandler<_hdlr_GameState>()->addComponent<GameState>()->setStopped(true);
	};

		// - a este método se le va a llamar cuando no haya más asteroides.
		// - desactivar todas las balas.
		// - actualizar los componentes correspondientes (Score, GameState, …).
	void onAsteroidsExtenction() {
		for (auto& b : mngr_->getGroupEntities<_grp_Bullet>()) {
			b->setActive(false);
		}
		mngr_->getHandler<_hdlr_GameState>()->addComponent<GameState>()->setFinished(true);
		mngr_->getHandler<_hdlr_GameState>()->addComponent<GameState>()->setStopped(true);
	};

		// - crear una entidad, añade sus componentes (Score y GameState) y asociarla
		// con el handler _hndlr_GameState.
	void init() override {
		Entity* e = mngr_->addEntity();
		auto sc = e->addComponent<Score>();
		auto gs = e->addComponent<GameState>();
		sc->points_ = 0;
		mngr_->setHandler<_hdlr_GameState>(e);
	}

		// - si el juego está parado y el jugador pulsa ENTER empieza una nueva ronda:
		// 1) añadir 10 asteroides llamando a addAsteroids del AsteroidsSystem.
		// 2) actualizar el estado del juego y el número de vidas (si es necesario)
		// en los componentes correspondientes (Score, Heath, GameState, …).
	void update() override {
		
		auto gt = mngr_->getHandler<_hdlr_GameState>()->addComponent<GameState>();
		auto health = mngr_->getHandler<_hdlr_Fighter>()->getComponent<Health>();
		auto ih = game_->getInputHandler();
		if (gt->isStopped() && ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN))
		{
			game_->getAudioMngr()->playMusic(Resources::ImperialMarch);
			if (health->getHealth() <= 0) {
				
				mngr_->getHandler<_hdlr_GameState>()->addComponent<Score>()->points_ = 0;
				mngr_->getHandler<_hdlr_Fighter>()->getComponent<Health>()->resetHealth();				
			}			
			mngr_->getSystem<AsteroidsSystem>()->addAsteroids(10);
			gt->setStopped(false);
		}
		
	}

};

