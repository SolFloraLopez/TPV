#include "AsteroidPool.h"

AsteroidPool::AsteroidPool() : Component(ecs::AsteroidPool),
	pool_([](Asteroid* o) {
		return o->inUse_;
	}) 
{}


AsteroidPool::~AsteroidPool() {}

void AsteroidPool::generateAsteroids(int n) {
}
void AsteroidPool::disablAll() {
}
//void AsteroidPool::onCollision(Asteroid* a, Bullet* b);
void AsteroidPool::getNumOfAsteroid() {

}
void AsteroidPool::getPool() {

}