#pragma once

#include "ecs.h"
#include "System.h"
#include "SDLGame.h"
#include "Manager.h"

class GameCtrlSystem: public System {
public:
	enum State : uint8_t {
		WAITING, READY, RUNNING, ROUNDOVER, GAMEOVER
	};

	GameCtrlSystem();
	void recieve(const msg::Message& msg) override;
	void init() override;
	void update() override;
	State getState() {
		return state_;
	}
	uint8_t getScore(uint8_t fighterId) {
		assert(fighterId >= 0 && fighterId <= 1);
		return score[fighterId];
	}

	

private:
	void resetScore();
	void startGame();
	void sendMyInfo();

	void onFighterDeath(uint8_t fighterId);


	uint8_t score[2];
	State state_;
};

