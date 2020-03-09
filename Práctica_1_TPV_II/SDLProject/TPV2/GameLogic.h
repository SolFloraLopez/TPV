#pragma once

#include "Component.h"
#include "ScoreManager.h"
#include "Transform.h"
#include "AsteroidPool.h"
#include "BulletsPool.h"
#include "Health.H"

class GameLogic: public Component {
public:
	GameLogic(Transform* fighterTR, AsteroidPool* asteroidPool, BulletsPool* bulletsPool, Health* health);
	virtual ~GameLogic();
	void init() override;
	void update() override;
private:
	Transform* fighterTR_;
	AsteroidPool* asteroidPool_;
	BulletsPool* bulletsPool_;
	Health* health_;
	ScoreManager *scoreManager_;
};

