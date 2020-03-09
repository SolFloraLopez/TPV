#pragma once

#include <vector>

#include "Manager.h"
#include "SDLGame.h"
#include "AsteroidPool.h"
#include "BulletsPool.h"

class PingPong {

public:
	PingPong();
	virtual ~PingPong();

	// from SDLGame
	void start();
	void stop();

private:
	void initGame();
	void closeGame();
	void handleInput();
	void update();
	void render();

	SDLGame* game_;
	EntityManager* entityManager_;
	AsteroidPool* asteroidPool_;
	BulletsPool* bulletsPool_;
	bool exit_;

	const static int _WINDOW_WIDTH_ = 640;
	const static int _WINDOW_HEIGHT_ = 480;

};
