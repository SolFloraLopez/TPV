#include "BulletsViewer.h"

BulletsViewer::BulletsViewer() : Component(ecs::BulletsViewer), tr_(nullptr) {}

BulletsViewer::~BulletsViewer() {}

void BulletsViewer::init()
{
	tr_ = GETCMP1_(Transform);
	tex_ = game_->getTextureMngr()->getTexture(Resources::Bullets);
}

void BulletsViewer::draw()
{
	SDL_Rect rect
		RECT(tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(),
			tr_->getH());

	tex_->render(game_->getRenderer(), rect, tr_->getRot());
}