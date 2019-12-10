#pragma once
#include "GameState.h"
#include <stack>

class GameStateMachine 
{
private:
	stack<GameState*> stateStack;
public:
	GameState currentState();
	void pushState();
	void changeSate();
	void popState();

};
