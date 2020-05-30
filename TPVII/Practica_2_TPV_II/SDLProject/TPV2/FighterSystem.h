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

	// - poner el caza en el centro con velocidad 0 y rotaci�n 0. No hace falta
	// desactivar la entidad (no dibujarla si el juego est� parado en RenderSystem).
	void onCollisionWithAsteroid(Entity* a) {
		a->setActive(false); //volver a activar?
	};

	// - crear la entidad del caza, a�adir sus componentes (Transform, Health, etc.)
	// y asociarla con el handler _hndlr_Fighter.
	void init() override {
		Entity* fighter = mngr_->addEntity();
		Vector2D pos(game_->getWindowWidth() / 2 - 6, game_->getWindowHeight() / 2 - 6);
		ftr = fighter->addComponent<Transform>(pos, Vector2D(),	50, 50, 0);
		Health* fighterH = fighter->addComponent<Health>(3);
		fighter->addComponent<ImageComponent>(game_->getTextureMngr()->getTexture(Resources::Airplanes));
		
		mngr_->setHandler<_hdlr_Fighter>(fighter);
	};
	// - si el juego est� parado no hacer nada.
	// - actualizar la velocidad del caza y moverlo como en la pr�ctica 1.
	void update() override {
		auto gt = mngr_->getHandler<_hdlr_GameState>()->getComponent<GameState>();
		if (!gt->isStopped())
		{	
			InputHandler* ih = InputHandler::instance();

			//movimiento
			if (ih->keyDownEvent()) {
				if (ih->isKeyDown(SDLK_UP)) { //acelerar
					ftr->velocity_.set(ftr->velocity_ + Vector2D(0, -1).rotate(ftr->rotation_) * 0.5);
				}
				else if (ih->isKeyDown(SDLK_RIGHT)) {
					ftr->rotation_=(int)floor(ftr->rotation_ + 5) % 360;
				}
				else if (ih->isKeyDown(SDLK_LEFT)) {
					ftr->rotation_ = (int)floor(ftr->rotation_ - 5) % 360;
				}
			}

			//rebote
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