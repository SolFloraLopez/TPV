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
	// - a este m�todo se le va a llamar cuando muere el caza.
	// - desactivar todos los asteroides y las balas.
	// - actualizar los componentes correspondientes (Score, Heath, GameState, �).
	void onFighterDeath() {
		for (auto& a : mngr_->getGroupEntities<_grp_Asteroid>()) {
			a->setActive(false);
		}
		for (auto& b : mngr_->getGroupEntities<_grp_Bullet>()) {
			b->setActive(false);
		}
		
		mngr_->getHandler<_hdlr_GameState>()->getComponent<GameState>()->setStopped(true);
		mngr_->getHandler<_hdlr_GameState>()->getComponent<GameState>()->setFinished(true);

	};

		// - a este m�todo se le va a llamar cuando no haya m�s asteroides.
		// - desactivar todas las balas.
		// - actualizar los componentes correspondientes (Score, GameState, �).
	void onAsteroidsExtenction() {
		for (auto& b : mngr_->getGroupEntities<_grp_Bullet>()) {
			b->setActive(false);
		}
		
		mngr_->getHandler<_hdlr_GameState>()->getComponent<GameState>()->setFinished(true);
		mngr_->getHandler<_hdlr_GameState>()->getComponent<GameState>()->setStopped(true);
	};

		// - crear una entidad, a�ade sus componentes (Score y GameState) y asociarla
		// con el handler _hndlr_GameState.
	void init() override {
		Entity* e = mngr_->addEntity();
		auto sc = e->addComponent<Score>();
		auto gs = e->addComponent<GameState>();
		sc->points_ = 0;
		mngr_->setHandler<_hdlr_GameState>(e);
	}

		// - si el juego est� parado y el jugador pulsa ENTER empieza una nueva ronda:
		// 1) a�adir 10 asteroides llamando a addAsteroids del AsteroidsSystem.
		// 2) actualizar el estado del juego y el n�mero de vidas (si es necesario)
		// en los componentes correspondientes (Score, Heath, GameState, �).
	void update() override {
		
		auto gt = mngr_->getHandler<_hdlr_GameState>()->getComponent<GameState>();
		auto ih = game_->getInputHandler();
		
		if (ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN))
		{
			if (gt->isStopped()) {
				mngr_->getSystem<AsteroidsSystem>()->addAsteroids(10);
				gt->setStopped(false);
				auto tr_ = mngr_->getHandler<_hdlr_Fighter>()->getComponent<Transform>();
				tr_->position_ = { game_->getWindowWidth() / 2.0, game_->getWindowHeight() / 2.0 };
				tr_->velocity_ = { 0.0,0.0 };
				
				if (gt->isFinished()) {
					mngr_->getHandler<_hdlr_GameState>()->getComponent<Score>()->points_ = 0;
					mngr_->getHandler<_hdlr_Fighter>()->getComponent<Health>()->resetHealth();
					gt->setFinished(false);
				}
			}
			
			game_->getAudioMngr()->playMusic(Resources::ImperialMarch);
			
			//resetear la posicion y los asteroides
			
			
		}
		
	}

};

