#pragma once
#include "ecs.h"
#include "Manager.h"
#include "ImageComponent.h"
#include "SDL_macros.h"
#include "SDLGame.h"
#include "System.h"
#include "Transform.h"
#include "Entity.h"
#include "Manager.h"
#include "Score.h"
#include "SDLGame.h"
#include "Texture.h"
#include "GameState.h"

class RenderSystem: public System {
public:

	void draw(Entity *e) {
		Transform *tr = e->getComponent<Transform>();
		ImageComponent *img = e->getComponent<ImageComponent>();
		SDL_Rect dest =
		RECT(tr->position_.getX(), tr->position_.getY(), tr->width_,
				tr->height_);
		img->tex_->render(dest, tr->rotation_);
	}

	void drawScore() {
		auto sc =
				mngr_->getHandler<_hdlr_GameState>()->getComponent<Score>();
		Texture scoreMsg(game_->getRenderer(), std::to_string(sc->points_),
				game_->getFontMngr()->getFont(Resources::ARIAL24),
				{ COLOR(0x0000ffff) });
		scoreMsg.render(game_->getWindowWidth() / 2 - scoreMsg.getWidth() / 2,
				10);

	}

	void drawLifes() {
		
	}

	
	// - dibujar asteroides, balas y caza (sólo si el juego no está parado).
	// - dibujar el marcador y las vidas (siempre).
	// - dibujar el mensaje correspondiente si el juego está parado (como en la
	// práctica 1: Press ENTER to start, Game Over, etc.)

	void update() override {
		auto gt = mngr_->getHandler<_hdlr_GameState>()->addComponent<GameState>();
		if (gt->state_ != gt->Parado)
		{
			// draw asteroids
			for (auto& e : mngr_->getGroupEntities<_grp_Asteroid>()) {
				if (e->isActive())draw(e);
			}
			// draw bullets
			for (auto& e : mngr_->getGroupEntities<_grp_Bullet>()) {
				if (e->isActive())draw(e);
			}
			// draw fighter
			draw(mngr_->getHandler<_hdlr_Fighter>());

			// draw score
			drawScore();

			//draw health
			drawLifes();
		}
		else if (gt->state_ == gt->Terminado) {
			//mensaje de game over
		}
		else{
			//mensaje de Press ENTER to start
		}
		// info message
		/*Texture msg(game_->getRenderer(),"Press ENTER to add More Stars", game_->getFontMngr()->getFont(Resources::ARIAL24),{COLOR(0xff0000ff)});
		msg.render(game_->getWindowWidth()/2-msg.getWidth()/2,game_->getWindowHeight()-msg.getHeight()-10);*/
	}
};

