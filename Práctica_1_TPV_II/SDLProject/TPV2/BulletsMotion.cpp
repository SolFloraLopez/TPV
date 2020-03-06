#include "BulletsMotion.h"
#include "Entity.h"

BulletsMotion::BulletsMotion() :
	Component(ecs::BulletsMotion), tr_(nullptr) {
}

BulletsMotion::~BulletsMotion() {
}

void BulletsMotion::init() {
	tr_ = GETCMP1_(Transform);
}

void BulletsMotion::update() {

	Vector2D v = tr_->getPos() + tr_->getVel();

	double y = v.getY();
	double x = v.getX();

	if (y <= 0 || y + tr_->getH() >= game_->getWindowHeight() || x <= 0 || x + tr_->getW() >= game_->getWindowWidth()) {
		//marcar como no usado		
	}
	
	tr_->setPos(v);
	tr_->setRot((int)floor(tr_->getRot() + 0.5) % 360);
}

