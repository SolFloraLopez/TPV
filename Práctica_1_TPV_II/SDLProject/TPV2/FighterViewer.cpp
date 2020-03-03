#include "FighterViewer.h"

FighterViewer::FighterViewer() : Component(ecs::FighterViewer), tr_(nullptr) {}

FighterViewer::~FighterViewer(){}

void FighterViewer::init()
{
	tr_ = GETCMP1_(Transform);
	tex_ = game_->getTextureMngr()->getTexture(Resources::Airplanes);
	clip_ = new SDL_Rect{ 47, 90, 207, 250 };
}

void FighterViewer::draw()
{
	SDL_Rect rect
		RECT(tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(),
			tr_->getH());

	tex_->render(game_->getRenderer(), rect, tr_->getRot(), clip_);
}