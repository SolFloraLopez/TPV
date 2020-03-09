#pragma once

#include "Component.h"
#include "ScoreManager.h"
#include "Transform.h"
#include "AsteroidPool.h"
#include "Health.h"

class GameCtrl: public Component {
public:
	GameCtrl(AsteroidPool* asteroidPool, Health* health);
	virtual ~GameCtrl();
	void init() override;
	void update() override;
	void draw() override;
private:
	AsteroidPool* asteroidPool_;
	Health* health_;
	ScoreManager *scoreManager_;
};

