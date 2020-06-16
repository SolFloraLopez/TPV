#pragma once

#include "System.h"

struct GameState;

class GameCtrlSystem: public System {
public:

	GameCtrlSystem();

	void init() override;
	void update() override;
	void recieve(const msg::Message& msg) override;

	// TODO: these methods should go private
	

private:
	void startGame();

	void onPacManDeath();
	void onNoMoreFood();

	GameState *gameState_;

};

