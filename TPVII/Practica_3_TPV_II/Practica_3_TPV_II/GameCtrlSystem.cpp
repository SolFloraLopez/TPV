#include "GameCtrlSystem.h"

#include <cassert>
#include <cstdint>
#include "ecs.h"
#include "Entity.h"
#include "FighterInfo.h"
#include "FightersSystem.h"
#include "Manager.h"

using ecs::CmpId;

GameCtrlSystem::GameCtrlSystem() :
		System(ecs::_sys_GameCtrl) {
	state_ = WAITING;
	resetScore();
}

void GameCtrlSystem::receive(const msg::Message& msg)
{
	switch (msg.id) {
	case msg::_PLAYER_INFO: {
		if (state_ == READY || msg.senderClientId == mngr_->getClientId())
			std::cout << "Client " << mngr_->getClientId() << " waiting" << endl;
			return;

		state_ = READY;
		std::cout << "Client " << mngr_->getClientId() << " ready" << endl;
		mngr_->send<msg::Message>(msg::_PLAYER_INFO);

		break; 
	}	
	case msg::_CLIENT_DISCONNECTED: {
		
		state_ = WAITING;
		//cambiar score a 0 y la ronda a 0
		break; }
	default:
		break; 
	}
}

void GameCtrlSystem::init() {
	state_ = WAITING;
	mngr_->send<msg::Message>(msg::_PLAYER_INFO);
	std::cout << "Client " << mngr_->getClientId() << " connected" << endl;
}

void GameCtrlSystem::update() {

	if (state_ == READY) {
		if (state_ != RUNNING) {
			InputHandler* ih = game_->getInputHandler();
			if (ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
				startGame();
			}
		}
	}
}

void GameCtrlSystem::startGame() {
	if (state_ == GAMEOVER) {
		resetScore();
	}
	mngr_->getSystem<FightersSystem>(ecs::_sys_Fighters)->resetFighterPositions();
	state_ = RUNNING;
}

void GameCtrlSystem::onFighterDeath(uint8_t fighterId) {
	assert(fighterId >= 0 && fighterId <= 1);

	uint8_t id = 1 - fighterId; // the id of the other player fighter

	state_ = ROUNDOVER;
	score[id]++;
	if (score[id] == 3)
		state_ = GAMEOVER;

}



void GameCtrlSystem::resetScore() {
	score[0] = score[1] = 0;
}
