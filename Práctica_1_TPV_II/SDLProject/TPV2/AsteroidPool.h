#pragma once
#include "Component.h"
#include "Transform.h"
#include "ObjectPool.h"
#include "BulletsPool.h"

class AsteroidPool : public Component {

public:
	struct Asteroid {
		Vector2D pos_;
		Vector2D vel_;
		int width_;
		int height_;
		double rot_;
		int gen_;
		bool inUse_ = false;
	};

	AsteroidPool();
	virtual ~AsteroidPool();
	void generateAsteroids(int n);
	void disablAll();
	void onCollision(Asteroid* a/*, BulletsPool::Bullet* b*/);
	int getNumOfAsteroid();
	const std::vector<Asteroid*>& getPool()
	{
		return pool_.getPool();
	}

private:
	ObjectPool<Asteroid, 30>pool_;
};

