#include "AsteroidPool.h"

	struct Asteroid {
		Vector2D pos_;
		Vector2D vel_;
		int width_;
		int height_;
		int rot_;
		int gen_;
		bool inUse_ = false;
	};

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

				double rand;
				double x;
				double y;

				if (i % 2 == 0) 
				{
					rand = SDLGame::instance()->getRandGen()->nextInt(0, 100);
					x = (game_->getWindowWidth() * rand) / 100;


					rand = SDLGame::instance()->getRandGen()->nextInt(0, 2);
					y = (game_->getWindowHeight() * rand) - 10 * rand;
				}

				else 
				{
					rand = SDLGame::instance()->getRandGen()->nextInt(0, 2);
					x = (game_->getWindowWidth() * rand) - 10 * rand;

					rand = SDLGame::instance()->getRandGen()->nextInt(0, 100);
					y = (game_->getWindowHeight() * rand) / 100;
				}

				o->pos_ = Vector2D(x, y); //en los bordes de la ventana
			
			
				x = SDLGame::instance()->getRandGen()->nextInt(-50,50);
				y = SDLGame::instance()->getRandGen()->nextInt(-50,50);
				Vector2D c = Vector2D((cx+x), (cy + y)); //posicion aleatoria en el centro de la ventana

				double m = SDLGame::instance()->getRandGen()->nextInt(1, 10);
				o->vel_ = Vector2D((c - o->pos_).normalize() * (m / 10.0));
				o->rot_ = 0;
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
	
	void AsteroidPool::onCollision(Asteroid* a/*, BulletsPool::Bullet* b*/)
	{
		a->inUse_ = false;
		if (a->gen_ > 0)
		{
			for (int i = 0; i < 2; i++) {
				Asteroid* o = pool_.getObj();
				if (o != nullptr) {

					Vector2D v = a->vel_.rotate(i * 45);
					Vector2D p = a->pos_ + v.normalize();

					o->vel_ = v;
					o->pos_ = p;
					o->rot_ = 0;
					o->gen_ = a->gen_-1;
					o->height_ = o->width_ = 10 + 3 * o->gen_;
					o->inUse_ = true;
				}
			}

		}
	}

	int AsteroidPool::getNumOfAsteroid() {
		int cont = 0;
		for (auto& o : pool_.getPool()) {
			if (o->inUse_ == true) {
				cont++;
			}
		}
		return cont;
	}