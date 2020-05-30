#pragma once

#include <vector>
#include <assert.h>

#include "SDL_macros.h"

#include "SDLGame.h"

class Manager;
class GameCtrlSystem;
class CollisionSystem;
class FighterSystem;
class FighterGunSystem;
class AsteroidsSystem;
class BulletsSystem;
class RenderSystem;


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
