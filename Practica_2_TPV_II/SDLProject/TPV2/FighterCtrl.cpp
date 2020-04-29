#include <iostream>
#include <math.h>
#include "FighterCtrl.h"
#include "InputHandler.h"
#include "Entity.h"
#include "Transform.h"

FighterCtrl::FighterCtrl() :
	FighterCtrl(SDLK_UP, SDLK_RIGHT, SDLK_LEFT) {
}

FighterCtrl::FighterCtrl(SDL_Keycode up, SDL_Keycode right, SDL_Keycode left) :
	Component(ecs::FighterCtrl), //
	up_(up), //
	right_(right), //
	left_(left),
	tr_(nullptr)//
{
}

FighterCtrl::~FighterCtrl() {
}

void FighterCtrl::init() {
	tr_ = GETCMP1_(Transform);
}

void FighterCtrl::update() {

	InputHandler* ih = InputHandler::instance();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(up_)) { //acelerar
			tr_->setVel(tr_->getVel() + Vector2D(0, -1).rotate(tr_->getRot()) * 0.5);
		}
		else if (ih->isKeyDown(right_)) {
			tr_->setRot((int)floor(tr_->getRot() + 5) % 360);			
		}
		else if (ih->isKeyDown(left_)) {
			tr_->setRot((int)floor(tr_->getRot() - 5) % 360);			
		}
	}	
}
