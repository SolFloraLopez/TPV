#include "AsteroidPool.h"

	AsteroidPool::AsteroidPool() : Component(ecs::AsteroidPool),
		pool_([](Asteroid* o) {
			return o->inUse_;
		}) 
	{}


	AsteroidPool::~AsteroidPool() {}

	void AsteroidPool::generateAsteroids(int n) {

		double cy = game_->getWindowHeight()/2;
		double cx = game_->getWindowWidth()/2;

		for (int i = 0; i < n; i++) {
			Asteroid* o = pool_.getObj();
			if (o != nullptr) {

				//o->pos_  en los bordes de la ventana
			
			
				double x = SDLGame::instance()->getRandGen()->nextInt(-50,50);
				double y = SDLGame::instance()->getRandGen()->nextInt(-50,50);
				Vector2D c = Vector2D((cx+x), (cy + y)); //posicion aleatoria en el centro de la ventana

				double m = SDLGame::instance()->getRandGen()->nextInt(1, 10);
				o->vel_ = Vector2D((c - o->pos_).normalize() * (m / 10.0));
			
				o->gen_ = SDLGame::instance()->getRandGen()->nextInt(1, 3);
				o->height_ = o->width_ = 10 + 3 * o->gen_;
				o->inUse_ = true;
			}
		}
	}
	void AsteroidPool::disablAll() {
		for (auto& o : pool_.getPool()) {
			o->inUse_ = false;
		}

	}
	//void AsteroidPool::onCollision(Asteroid* a, Bullet* b);

	int AsteroidPool::getNumOfAsteroid() {
		int cont = 0;
		for (auto& o : pool_.getPool()) {
			if (o->inUse_ == true) {
				cont++;
			}
		}
		return cont;
	}
	void AsteroidPool::getPool() {
		/*return*/pool_.getPool();
	}