#include "Gun.h"
#include "InputHandler.h"
#include "Entity.h"
#include "Transform.h"

Gun::Gun(BulletsPool* pool) : Gun(SDLK_SPACE)
{
	pool_ = pool;
}

Gun::Gun(SDL_Keycode space) :
	Component(ecs::Gun), //
	space_(space), //
	tr_(nullptr)//
{
}

Gun::~Gun() {
}

void Gun::init() {
	tr_ = GETCMP1_(Transform);
}

void Gun::update() {

	InputHandler* ih = InputHandler::instance();

	Vector2D bulletPos = tr_->getPos() + Vector2D(tr_->getW() / 2, tr_->getH() / 2) + Vector2D(0, -(tr_->getH() / 2 + 5.0)).rotate(tr_->getRot());
	Vector2D bulletVel = Vector2D(0, -1).rotate(tr_->getRot())*2;


	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(space_) && game_->getTime() - time_ > 250) {
			pool_->shoot(bulletPos, bulletVel, 5, 5);
			game_->getAudioMngr()->playChannel(Resources::Gunshot, 0);
			time_ = game_->getTime();
		}
	}
}