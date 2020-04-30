#include "BulletsPool.h"
//
//	BulletsPool::BulletsPool() : Component(ecs::BulletsPool),
//		pool_([](Bullet* o) {
//			return o->inUse_;
//		})
//	{}
//
//
//	BulletsPool::~BulletsPool() {}
//
//	void BulletsPool::shoot(Vector2D pos, Vector2D vel, double w, double h) {
//
//			Bullet* o = pool_.getObj();
//			if (o != nullptr) {
//
//				o->pos_ = pos;
//				o->vel_ = vel;
//				o->width_ = w;
//				o->height_ = h;
//				o->inUse_ = true;
//			}
//	}
//
//	void BulletsPool::disablAll() {
//		for (auto& o : pool_.getPool()) {
//			o->inUse_ = false;
//		}
//
//	}
//
//	void BulletsPool::onCollision(Bullet* b/*, AsteroidPool::Asteroid* a*/)
//	{
//		b->inUse_ = false;
//	}