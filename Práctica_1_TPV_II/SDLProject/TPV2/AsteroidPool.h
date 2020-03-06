#pragma once
#include "Component.h"
#include "Transform.h"
#include "ObjectPool.h"

class AsteroidPool : public Component {

public:
	struct Asteroid {
		Vector2D pos_;
		Vector2D vel_;
		int width_;
		int height_;
		int rot_;
		int gen_;
		bool inUse_ = false;
	};

	AsteroidPool();
	virtual ~AsteroidPool();

	void generateAsteroids(int n);
	void disablAll();
	//void onCollision(Asteroid* a, Bullet* b);
	void getNumOfAsteroid();
	void getPool();

private:
	ObjectPool<Asteroid, 30>pool_;

};