#pragma once
#include "System.h"
#include "BulletsSystem.h"
#include "InputHandler.h"
#include "Transform.h"

class FighterGunSystem : public System {
public:
	BulletsSystem* b;
	Transform* tr_;
	Uint32 time_;
	// - si el juego está parado no hacer nada.
	// - si el jugador pulsa SPACE, llamar a shoot(...) del BulletsSystem para añadir
	// una bala al juego -- se puede disparar sólo una bala cada 0.25sec.
	void update() override {
		InputHandler* ih = InputHandler::instance();
		if (ih->keyDownEvent()) 
		{
			if (ih->isKeyDown(SDLK_SPACE) /*&& game_->getTime() - time_ > 250*/) {
				
				Vector2D bulletPos = tr_->position_ + Vector2D(tr_->width_ / 2, tr_->height_ / 2) + Vector2D(0, -(tr_->height_ / 2 + 5.0)).rotate(tr_->rotation_);
				Vector2D bulletVel = Vector2D(0, -1).rotate(tr_->rotation_) * 2;
				
				b->shoot(bulletPos, bulletVel, 5, 5);
				//game_->getAudioMngr()->playChannel(Resources::Gunshot, 0);
				time_ = game_->getTime();
			}
		}
	};
};