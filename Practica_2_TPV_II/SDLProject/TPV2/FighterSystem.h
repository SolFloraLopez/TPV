#pragma once
#include <cmath>
#include "SDL_macros.h"
#include "System.h"
#include "Entity.h"
#include "Transform.h"
#include "Manager.h"
#include "SDLGame.h"
#include "Health.h"
#include "GameState.h"

class FighterSystem : public System {
private:
	Transform* ftr;
	double speedLimit = 2.0;
public:

	// - poner el caza en el centro con velocidad 0 y rotación 0. No hace falta
	// desactivar la entidad (no dibujarla si el juego está parado en RenderSystem).
	void onCollisionWithAsteroid(Entity* a) {
		a->setActive(false); //volver a activar?
	};

	// - crear la entidad del caza, añadir sus componentes (Transform, Health, etc.)
	// y asociarla con el handler _hndlr_Fighter.
	void init() override {
		Entity* fighter = mngr_->addEntity();
		ftr = fighter->addComponent<Transform>(Vector2D(
			game_->getWindowWidth() / 2 - 6, game_->getWindowHeight() / 2 - 6), Vector2D(),
			50, 50, 0);
		Health* fighterH = fighter->addComponent<Health>(3);
		fighter->addComponent<ImageComponent>(game_->getTextureMngr()->getTexture(Resources::Fighter));
		//fighter->addComponent<FighterViewer>();
		/*fighter->addComponent<FighterMotion>();
		fighter->addComponent<FighterCtrl>();
		fighter->addComponent<Gun>(bulletsPool_);*/

		mngr_->setHandler<_hdlr_Fighter>(fighter);
	};
	// - si el juego está parado no hacer nada.
	// - actualizar la velocidad del caza y moverlo como en la práctica 1.
	void update() override {
		auto gt = mngr_->getHandler<_hdlr_GameState>()->addComponent<GameState>();
		if (gt->state_ != gt->Parado) 
		{			
			Vector2D v = ftr->position_ + ftr->velocity_;

			double y = v.getY();
			double x = v.getX();

			if (y <= 0) {

				v.setY(0);
				ftr->position_.setY((y + ftr->velocity_.getY()));
				ftr->velocity_.setY(ftr->velocity_.getY() * -1);
			}
			else if (y + ftr->height_ >= game_->getWindowHeight()) {

				v.setY(game_->getWindowHeight() - ftr->height_);
				ftr->position_.setY(y - ftr->velocity_.getY());
				ftr->velocity_.setY(ftr->velocity_.getY() * -1);
			}

			if (x <= 0)
			{
				v.setX(0);
				ftr->position_.setX((x + ftr->velocity_.getX()));
				ftr->velocity_.setX(ftr->velocity_.getX() * -1);
			}

			else if (x + ftr->width_ >= game_->getWindowWidth())
			{
				v.setX(game_->getWindowWidth() - ftr->width_);
				ftr->position_.setX(x - ftr->velocity_.getX());
				ftr->velocity_.setX(ftr->velocity_.getX() * -1);
			}

			if (abs(ftr->velocity_.getX()) > speedLimit || abs(ftr->velocity_.getY()) > speedLimit) {
				ftr->velocity_.set(ftr->velocity_.normalize() * speedLimit);
			}

			ftr->velocity_.set(ftr->velocity_ * 0.995);

			ftr->position_.set(v);
		}
	};
	
};