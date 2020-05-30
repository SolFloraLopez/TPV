#pragma once
#include <cmath>
#include "SDL_macros.h"
#include "AsteroidLifeTime.h"
#include "System.h"
#include "Transform.h"
#include "Entity.h"
#include "Manager.h"
#include "AsteroidPool.h"
#include "SDLGame.h"
#include "GameState.h"


class AsteroidsSystem : public System {
private:
	//std::size_t numOfAsteroids_;
	int numOfAsteroids_;

	
	double x;
	double y;
	Vector2D pos;
	Vector2D vel;
	double w, h, gen;

public:
	int getNumAsteroids() 
	{
		numOfAsteroids_ = 0;
		for (auto& a : mngr_->getGroupEntities<_grp_Asteroid>())
		{
			if (a->isActive()) { numOfAsteroids_++; }
		}
		return numOfAsteroids_;
	}

	void disableAll() {
		for (auto& a : mngr_->getGroupEntities<_grp_Asteroid>())
		{
			a->setActive(false);			
		}
	}
	// - añadir n asteroides al juego como en la práctica 1 pero usando entidades.
	// - no olvidar añadir los asteroides al grupo _grp_Asteroid.
	void addAsteroids(int n) {		
		
		double cy = game_->getWindowHeight() / 2;
		double cx = game_->getWindowWidth() / 2;
		for (int i = 0; i < n; i++) {
			
		
			double rand;				
		
			if (i % 2 == 0) {	
				rand = SDLGame::instance()->getRandGen()->nextInt(0, 100);
				x = (game_->getWindowWidth() * rand) / 100;
				
				rand = SDLGame::instance()->getRandGen()->nextInt(0, 2);
				y = (game_->getWindowHeight() * rand) - 10 * rand;
			}
		
			else {
				rand = SDLGame::instance()->getRandGen()->nextInt(0, 2);
				x = (game_->getWindowWidth() * rand) - 10 * rand;
		
				rand = SDLGame::instance()->getRandGen()->nextInt(0, 100);
				y = (game_->getWindowHeight() * rand) / 100;
			}
		
			pos = Vector2D(x, y); //en los bordes de la ventana	
					
			x = SDLGame::instance()->getRandGen()->nextInt(-50,50);
			y = SDLGame::instance()->getRandGen()->nextInt(-50,50);
			Vector2D c = Vector2D((cx+x), (cy + y)); //posicion aleatoria en el centro de la ventana
		
			double m = SDLGame::instance()->getRandGen()->nextInt(1, 10);
			vel = Vector2D((c - pos).normalize() * (m / 10.0));
			//o->rot_ = 0;
			gen = SDLGame::instance()->getRandGen()->nextInt(1, 3);
			h= w = 10 + 3 * gen;			

			Entity* a = mngr_->addEntity<AsteroidPool>(pos,vel,w,h,gen);
			if (a != nullptr) {
				a->setActive(true);
				a->addToGroup<_grp_Asteroid>();
			}
				
			
		}
	};

	// - desactivar el asteroide “a” y crear 2 asteroides como en la práctica 1.
	void onCollisionWithBullet(Entity* a, Entity* b) {
		a->setActive(false);		
		AsteroidLifeTime* st = a->getComponent<AsteroidLifeTime>();
		Transform* tr = a->getComponent<Transform>();
		if (st->lifeTime_ > 0)
		{
			for (int i = 0; i < 2; i++) {

				Vector2D v = tr->velocity_.rotate(i * 45);
				Vector2D p = tr->position_ + v.normalize();

				Entity* ast = mngr_->addEntity<AsteroidPool>(p, v, 10 + 3 * st->lifeTime_, 10 + 3 * st->lifeTime_, st->lifeTime_ - 1);
				if (ast != nullptr) {
					ast->setActive(true);
					ast->addToGroup<_grp_Asteroid>();
				}					
				//sumas los dos que se crean
			}

		}
	};

	// - si el juego está parado no hacer nada.
	// - mover los asteroides como en la práctica 1.
	void update() override {
		auto gt = mngr_->getHandler<_hdlr_GameState>()->getComponent<GameState>();
		if (!gt->isStopped()) {
			
			for (auto& a : mngr_->getGroupEntities<_grp_Asteroid>())
			{
				if (a->isActive())					
				{
					auto atr = a->getComponent<Transform>();
					Vector2D v = atr->position_ + atr->velocity_;

					if (v.getX() < 0) v.setX(game_->getWindowWidth());
					else if (v.getX() > game_->getWindowWidth()) v.setX(0);

					if (v.getY() < 0) v.setY(game_->getWindowHeight());
					else if (v.getY() > game_->getWindowHeight()) v.setY(0);

					atr->position_ = v;
					atr->rotation_ = atr->rotation_ + 0.5;

					
				}
			}
		}
		else {
		}
		
	};
	
};