#include "AsteroidsViewer.h"

AsteroidsViewer::AsteroidsViewer() : Component(ecs::AsteroidsViewer), tr_(nullptr) {}

AsteroidsViewer::~AsteroidsViewer() {}

void AsteroidsViewer::init()
{
	tr_ = GETCMP1_(Transform);
	tex_ = game_->getTextureMngr()->getTexture(Resources::Asteroids);
}

void AsteroidsViewer::draw()
{
	SDL_Rect rect
		RECT(tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(),
			tr_->getH());

	tex_->render(game_->getRenderer(), rect, tr_->getRot());
}