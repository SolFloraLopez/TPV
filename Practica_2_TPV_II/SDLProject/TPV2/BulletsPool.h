#pragma once
#include "ecs.h"
#include "Entity.h"
#include "ImageComponent.h"
#include "ObjectPool.h"
#include "Singleton.h"
#include "LifeTime.h"
#include "Rotation.h"
#include "Transform.h"


class BulletsPool : public Singleton<BulletsPool> {
	friend Singleton<BulletsPool>;
public:
	virtual ~BulletsPool() {
	}

	template<typename ...Targs>
	inline static Entity* construct(Targs&&...args) {
		return StarsPool::instance()->construct_(std::forward<Targs>(args)...);
	}

	inline static void destroy(Entity* p) {
		BulletsPool::instance()->destroy_(p);
	}

	inline Entity* construct_(Vector2D pos, Vector2D vel, double width, double height) {
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
	BulletsPool() :
		BulletsPool(10) {
	}
	BulletsPool(std::size_t n) :
		pool_(n) {
		for (Entity* e : pool_.getPool()) {
			e->addComponent<Transform>();
			e->addComponent<LifeTime>();
			e->addComponent<Rotation>();
			e->addComponent<ImageComponent>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Star));
		}
	}

	ObjectPool<Entity> pool_;
};


//#pragma once
//#include "Component.h"
//#include "Transform.h"
//#include "ObjectPool.h"
//#include "AsteroidPool.h"
//
//
//class BulletsPool : public Component {
//
//public:
//	struct Bullet {
//		Vector2D pos_;
//		Vector2D vel_;
//		int width_;
//		int height_;
//		int rot_;
//		bool inUse_ = false;
//	};
//
//	BulletsPool();
//	virtual ~BulletsPool();
//
//	void shoot(Vector2D pos, Vector2D vel, double w, double h);
//	void disablAll();
//	void onCollision(Bullet* b/*, AsteroidPool::Asteroid*a*/);
//
//	const std::vector<Bullet*>& getPool()
//	{
//		return pool_.getPool();
//	}
//
//private:
//	ObjectPool<Bullet, 10>pool_;
//
//};
//
