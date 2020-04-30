#pragma once
#include <cmath>
#include "SDL_macros.h"
#include "System.h"
#include "Entity.h"
#include "Transform.h"
#include "Manager.h"
#include "SDLGame.h"
#include "Health.h"

class FighterSystem : public System {
public:
	// - poner el caza en el centro con velocidad 0 y rotación 0. No hace falta
	// desactivar la entidad (no dibujarla si el juego está parado en RenderSystem).
	void onCollisionWithAsteroid(Entity* a) {
		a->setActive(false);
	};

	// - crear la entidad del caza, añadir sus componentes (Transform, Health, etc.)
	// y asociarla con el handler _hndlr_Fighter.
	void init() override {
		Entity* fighter = mngr_->addEntity();
		Transform* fighterTR = fighter->addComponent<Transform>();		
		Health* fighterH = fighter->addComponent<Health>(3);
		//fighter->addComponent<FighterViewer>();
		/*fighter->addComponent<FighterMotion>();
		fighter->addComponent<FighterCtrl>();
		fighter->addComponent<Gun>(bulletsPool_);*/

		fighterTR->position_.set(game_->getWindowWidth() / 2 - 6, game_->getWindowHeight() / 2 - 6);
		fighterTR->width_ = 50;
		fighterTR->height_ = 50;

		mngr_->setHandler<_hdlr_Fighter>(fighter);
	};
	// - si el juego está parado no hacer nada.
	// - actualizar la velocidad del caza y moverlo como en la práctica 1.
	void update() override {};
};