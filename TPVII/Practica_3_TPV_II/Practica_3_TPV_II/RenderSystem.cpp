#include "RenderSystem.h"

#include "ecs.h"
#include "GameCtrlSystem.h"
#include "Manager.h"
#include "SDL_macros.h"
#include "SDLGame.h"

#include "Image.h"
#include "Transform.h"
#include "Texture.h"

RenderSystem::RenderSystem() :
		System(ecs::_sys_Render) {
}

void RenderSystem::update() {
	for (auto &e : mngr_->getGroupEntities(ecs::_grp_Fighters)) {
		drawImage(e); // auto cast from unique_ptr to Entity*
	}

	for (auto &e : mngr_->getGroupEntities(ecs::_grp_Bullets))
		drawImage(e); // auto cast from unique_ptr to Entity*

	drawCtrlMessages();
	drawScore();
	drawNames();
}

void RenderSystem::drawImage(Entity *e) {
	Transform *tr = e->getComponent<Transform>(ecs::Transform);
	Texture *tex = e->getComponent<Image>(ecs::Image)->tex_;

	SDL_Rect dest =
	RECT(tr->position_.getX(), tr->position_.getY(), tr->width_,
			tr->height_);
	tex->render(dest, tr->rotation_);
}

void RenderSystem::drawCtrlMessages() {
	auto gameState =
		mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->getState();
	if (gameState == GameCtrlSystem::WAITING) {
		auto msgTex = game_->getTextureMngr()->getTexture(
			Resources::WaitingForPlayer);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
			(game_->getWindowHeight() - msgTex->getHeight() - 10));
	}
	else if (gameState != GameCtrlSystem::RUNNING) {
		auto msgTex = game_->getTextureMngr()->getTexture(
			Resources::PressEnter);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
			(game_->getWindowHeight() - msgTex->getHeight() - 10));
	}

	if (gameState == GameCtrlSystem::GAMEOVER) {

		auto gameCtrl = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);
		Resources::TextureId message;
		uint8_t id = mngr_->getClientId();

		if (gameCtrl->getScore(id) > gameCtrl->getScore(1 - id)) message = Resources::Win;
		else if (gameCtrl->getScore(id) < gameCtrl->getScore(1 - id)) message = Resources::Loss;
		else message = Resources::Draw;

		auto msgTex = game_->getTextureMngr()->getTexture(message);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
			(game_->getWindowHeight() - msgTex->getHeight()) / 2);

	}

}

void RenderSystem::drawScore() {
	auto gameCtrl = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);

	Texture scoreTex(game_->getRenderer(),
			to_string(gameCtrl->getScore(0)) + " - "
					+ to_string(gameCtrl->getScore(1)),
			game_->getFontMngr()->getFont(Resources::ARIAL24),
			{ COLOR(0x111122ff) });
	scoreTex.render(game_->getWindowWidth() / 2 - scoreTex.getWidth() / 2, 10);
}

void RenderSystem::drawNames() {
	Texture myName(game_->getRenderer(), mngr_->getName(), game_->getFontMngr()->getFont(Resources::ARIAL24), { COLOR(0x111122ff) });
	Texture opName(game_->getRenderer(), mngr_->getOpName(), game_->getFontMngr()->getFont(Resources::ARIAL24), { COLOR(0x111122ff) });
	SDL_Rect whiteRect;
	SDL_SetRenderDrawColor(game_->getRenderer(), 255, 255, 255, 255);

	if (mngr_->getClientId() == 1) {
		whiteRect = RECT((game_->getWindowWidth() / 4) * 3 - myName.getWidth() / 2, 10, myName.getWidth(), myName.getHeight());
		SDL_RenderFillRect(game_->getRenderer(), &whiteRect);
		myName.render((game_->getWindowWidth() / 4) * 3 - myName.getWidth() / 2, 10);
		opName.render((game_->getWindowWidth() / 4) - opName.getWidth() / 2, 10);
	}
	else {
		whiteRect = RECT((game_->getWindowWidth() / 4) - myName.getWidth() / 2, 10, myName.getWidth(), myName.getHeight());
		SDL_RenderFillRect(game_->getRenderer(), &whiteRect);
		opName.render((game_->getWindowWidth() / 4) * 3 - opName.getWidth() / 2, 10);
		myName.render((game_->getWindowWidth() / 4) - myName.getWidth() / 2, 10);
	}

	
}