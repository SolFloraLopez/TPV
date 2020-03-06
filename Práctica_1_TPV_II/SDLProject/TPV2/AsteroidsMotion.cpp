#include "AsteroidsMotion.h"
#include "Entity.h"

AsteroidsMotion::AsteroidsMotion() :
	Component(ecs::AsteroidsMotion), tr_(nullptr) {
}

AsteroidsMotion::~AsteroidsMotion() {
}

void AsteroidsMotion::init() {
	tr_ = GETCMP1_(Transform);
}

void AsteroidsMotion::update() {

	Vector2D v = tr_->getPos() + tr_->getVel();

	double y = v.getY();
	double x = v.getX();

	if (y <= 0) {

		/*v.setY(0);
		tr_->setPosY(y + tr_->getVel().getY());
		tr_->setVelY(tr_->getVel().getY() * -1);*/
	}
	else if (y + tr_->getH() >= game_->getWindowHeight()) {

		/*v.setY(game_->getWindowHeight() - tr_->getH());
		tr_->setPosY(y - tr_->getVel().getY());
		tr_->setVelY(tr_->getVel().getY() * -1);*/
	}

	if (x <= 0)
	{
	/*	v.setX(0);
		tr_->setPosX(x + tr_->getVel().getX());
		tr_->setVelX(tr_->getVel().getX() * -1);*/
	}

	else if (x + tr_->getW() >= game_->getWindowWidth())
	{
		//v.setX(game_->getWindowWidth() - tr_->getW());
		//tr_->setPosX(x - tr_->getVel().getX());
		//tr_->setVelX(tr_->getVel().getX() * -1);
	}

	tr_->setPos(v);
	tr_->setRot((int)floor(tr_->getRot() + 0.5) % 360);
}

