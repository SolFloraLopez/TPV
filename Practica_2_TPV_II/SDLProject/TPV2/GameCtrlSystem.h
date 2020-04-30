#pragma once

#include "ecs.h"
#include "StarsSystem.h"
#include "System.h"
#include "Score.h"


class GameCtrlSystem: public System {
public:
	// - a este m�todo se le va a llamar cuando muere el caza.
	// - desactivar todos los asteroides y las balas.
	// - actualizar los componentes correspondientes (Score, Heath, GameState, �).
	void onFighterDeath() {};

		// - a este m�todo se le va a llamar cuando no haya m�s asteroides.
		// - desactivar todas las balas.
		// - actualizar los componentes correspondientes (Score, GameState, �).
	void onAsteroidsExtenction() {};

		// - crear una entidad, a�ade sus componentes (Score y GameState) y asociarla
		// con el handler _hndlr_GameState.
	void init() override {
		Entity* e = mngr_->addEntity();
		auto sc = e->addComponent<Score>();
		sc->points_ = 0;
		mngr_->setHandler<_hdlr_GameState>(e);
	}

		// - si el juego est� parado y el jugador pulsa ENTER empieza una nueva ronda:
		// 1) a�adir 10 asteroides llamando a addAsteroids del AsteroidsSystem.
		// 2) actualizar el estado del juego y el n�mero de vidas (si es necesario)
		// en los componentes correspondientes (Score, Heath, GameState, �).
	void update() override {
		auto ih = game_->getInputHandler();

		if ( ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
			mngr_->getSystem<StarsSystem>()->addStars(10);
		}
	}

};

