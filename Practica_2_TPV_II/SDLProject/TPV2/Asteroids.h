#pragma once
#pragma once

#include <vector>

#include "CollisionSystem.h"
#include "GameCtrlSystem.h"
#include "Manager.h"
#include "FighterSystem.h"
#include "FighterGunSystem.h"
#include "AsteroidsSystem.h"
#include "BulletsSystem.h"
#include "RenderSystem.h"
#include "SDLGame.h"

//#include "AsteroidPool.h"
//#include "BulletsPool.h"
//#include "Health.h"

class Asteroids {

public:
	Asteroids();
	virtual ~Asteroids();

	// from SDLGame
	void start();
	void stop();

private:
	void initGame();
	void closeGame();

	SDLGame* game_;
	Manager* mngr_;
	bool exit_;

	RenderSystem* renderSystem_;
	CollisionSystem* collisionSystem_;
	GameCtrlSystem* gameCtrlSystem_;
	FighterSystem* fighterSystem_;
	FighterGunSystem* fighterGunSystem_;
	AsteroidsSystem* asteroidsSystem_;
	BulletsSystem* bulletsSystem_;

	/*AsteroidPool* asteroidPool_;
	BulletsPool* bulletsPool_;
	Health* health_;*/
	

	const static int _WINDOW_WIDTH_ = 640;
	const static int _WINDOW_HEIGHT_ = 480;

};
