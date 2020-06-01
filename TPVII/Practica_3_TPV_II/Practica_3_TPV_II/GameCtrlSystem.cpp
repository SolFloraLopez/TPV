#include "GameCtrlSystem.h"

#include <cassert>
#include <cstdint>
#include "ecs.h"
#include "Entity.h"
#include "FighterInfo.h"
#include "FightersSystem.h"
#include "Manager.h"
#include "BulletsSystem.h"

using ecs::CmpId;

GameCtrlSystem::GameCtrlSystem() :
		System(ecs::_sys_GameCtrl) {
	state_ = WAITING;
	resetScore();
}

void GameCtrlSystem::recieve(const msg::Message& msg)
{
	switch (msg.id) {
	case msg::_PLAYER_INFO: {
		if (state_ == READY || msg.senderClientId == mngr_->getClientId()) {
			std::cout << "Client " << mngr_->getClientId() << " waiting" << endl;
			std::cout << "sender: " << msg.senderClientId << endl;
			std::cout << state_ << endl;
			return;
		}

		state_ = READY;
		std::cout << "Client " << mngr_->getClientId() << " ready" << endl;
		mngr_->send<msg::Message>(msg::_PLAYER_INFO);

		break; 
	}	
	case msg::_CLIENT_DISCONNECTED: {
		
		state_ = WAITING;
		//cambiar score a 0 y la ronda a 0
		break; 
	}
	case msg::_START_REQ: {
		if (state_ != RUNNING && mngr_->getClientId() == 0) 
			mngr_->send<msg::Message>(msg::_START_GAME);
		break;
	}		
	case msg::_START_GAME: {
		startGame();
		break;
	}
	case msg::_PLAYER_HIT: {
		onFighterDeath(static_cast<const msg::PlayerHitMsg&>(msg).player);
		break;
	}	
	case msg::_FIGHTERS_COLLIDE: {
		onFighterCrash();
		break;
	}
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
	if (state_ != RUNNING && state_ != WAITING) {
		InputHandler* ih = game_->getInputHandler();
		if (ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
			mngr_->send<msg::Message>(msg::_START_REQ);
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
	mngr_->getSystem<BulletsSystem>(ecs::_sys_Bullets)->disableAll();
	score[id]++;
	if (score[id] == 3)
		state_ = GAMEOVER;

}

void GameCtrlSystem::onFighterCrash() 
{
	state_ = ROUNDOVER;
	mngr_->getSystem<BulletsSystem>(ecs::_sys_Bullets)->disableAll();
}



void GameCtrlSystem::resetScore() {
	score[0] = score[1] = 0;
}
