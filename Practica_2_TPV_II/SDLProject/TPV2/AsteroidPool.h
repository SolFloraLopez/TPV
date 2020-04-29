#pragma once
#include "ecs.h"
#include "Entity.h"
#include "ImageComponent.h"
#include "ObjectPool.h"
#include "Singleton.h"
#include "LifeTime.h"
#include "Rotation.h"
#include "Transform.h"


class AsteroidPool : public Singleton<AsteroidPool> {
	friend Singleton<AsteroidPool>;
public:
	virtual ~AsteroidPool() {
	}

	template<typename ...Targs>
	inline static Entity* construct(Targs&&...args) {
		return AsteroidPool::instance()->construct_(std::forward<Targs>(args)...);
	}

	inline static void destroy(Entity* p) {
		AsteroidPool::instance()->destroy_(p);
	}

	inline Entity* construct_(Vector2D pos, Vector2D vel, double width, double height, int generations) {
		Entity* e = pool_.getObj();
		if (e != nullptr) {
			e->setActive(true);
			Transform* tr = e->getComponent<Transform>();
			tr->position_.set(pos);
			tr->width_ = width;
			tr->height_ = height;
			tr->velocity_ = vel;
			//LifeTime* st = e->getComponent<LifeTime>();
			//st->lifeTime_ = lifeTime * 1000;
			//st->creatiomTime_ = SDLGame::instance()->getTime();
			//e->getComponent<Rotation>()->rotation_ = r;
		}
		return e;
	}

	inline void destroy_(Entity* p) {
		pool_.relObj(p);
	}

private:
	AsteroidPool() :
		AsteroidPool(10) {
	}
	AsteroidPool(std::size_t n) :
		pool_(n) {
		for (Entity* e : pool_.getPool()) {
			e->addComponent<Transform>();
			//e->addComponent<LifeTime>();
			e->addComponent<Rotation>();
			e->addComponent<ImageComponent>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Asteroids));
		}
	}

	ObjectPool<Entity> pool_;
};


//#pragma once
//#include "Component.h"
//#include "Transform.h"
//#include "ObjectPool.h"
//#include "BulletsPool.h"
//
//class AsteroidPool : public Component {
//
//public:
//	struct Asteroid {
//		Vector2D pos_;
//		Vector2D vel_;
//		int width_;
//		int height_;
//		double rot_;
//		int gen_;
//		bool inUse_ = false;
//	};
//
//	AsteroidPool();
//	virtual ~AsteroidPool();
//	void generateAsteroids(int n);
//	void disablAll();
//	void onCollision(Asteroid* a/*, BulletsPool::Bullet* b*/);
//	int getNumOfAsteroid();
//	const std::vector<Asteroid*>& getPool()
//	{
//		return pool_.getPool();
//	}
//
//private:
//	ObjectPool<Asteroid, 5>pool_;
//};
//
