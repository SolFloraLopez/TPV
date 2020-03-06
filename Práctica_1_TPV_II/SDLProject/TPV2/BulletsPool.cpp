#include "BulletsPool.h"

	BulletsPool::BulletsPool() : Component(ecs::BulletsPool),
		pool_([](Bullet* o) {
			return o->inUse_;
		})
	{}


	BulletsPool::~BulletsPool() {}

	void BulletsPool::shoot(Vector2D pos, Vector2D vel, double w, double h) {

		//double cy = game_->getWindowHeight() / 2;
		//double cx = game_->getWindowWidth() / 2;

		//for (int i = 0; i < n; i++) {
		//	Bullet* o = pool_.getObj();
		//	if (o != nullptr) {

		//		//o->pos_  en los bordes de la ventana


		//		double x = SDLGame::instance()->getRandGen()->nextInt(-50, 50);
		//		double y = SDLGame::instance()->getRandGen()->nextInt(-50, 50);
		//		Vector2D c = Vector2D((cx + x), (cy + y)); //posicion aleatoria en el centro de la ventana

		//		double m = SDLGame::instance()->getRandGen()->nextInt(1, 10);
		//		o->vel_ = Vector2D((c - o->pos_).normalize() * (m / 10.0));

		//		o->gen_ = SDLGame::instance()->getRandGen()->nextInt(1, 3);
		//		o->height_ = o->width_ = 10 + 3 * o->gen_;
		//		o->inUse_ = true;
		//	}
		//}
	}

	void BulletsPool::disablAll() {
		for (auto& o : pool_.getPool()) {
			o->inUse_ = false;
		}

	}
	//void AsteroidPool::onCollision(Asteroid* a, Bullet* b);


	void BulletsPool::getPool() {
		/*return*/pool_.getPool();
	}