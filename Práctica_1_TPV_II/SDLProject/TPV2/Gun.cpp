#include "Gun.h"
#include "InputHandler.h"
#include "Entity.h"
#include "Transform.h"
//#include "BulletPool.h"

Gun::Gun() :
	Gun(SDLK_SPACE) {
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

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(space_)) {
			//bulletsPool.shoot();
		}
	}
}