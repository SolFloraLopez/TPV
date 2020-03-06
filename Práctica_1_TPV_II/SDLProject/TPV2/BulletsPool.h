#pragma once
#include "Component.h"
#include "Transform.h"
#include "ObjectPool.h"

class BulletsPool : public Component {

public:
	struct Bullet {
		Vector2D pos_;
		Vector2D vel_;
		int width_;
		int height_;
		int rot_;
		bool inUse_ = false;
	};

	BulletsPool();
	virtual ~BulletsPool();

	void shoot(Vector2D pos, Vector2D vel, double w, double h);
	void disablAll();
	//void onCollision(Bullet* b,Asteroid* a);
	void getPool();

private:
	ObjectPool<Bullet, 10>pool_;

};