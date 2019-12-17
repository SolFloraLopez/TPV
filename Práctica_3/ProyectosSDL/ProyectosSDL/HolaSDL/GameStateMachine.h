#pragma once
#include "GameState.h"
#include <stack>

class GameStateMachine 
{
private:
	stack<GameState*> stateStack;
	string flag = "";
public:
	GameState* currentState();
	void pushState(GameState* state);
	void changeState(GameState* state);
	void popState();
	void setFlag(string thisFlag);
	string getFlag();
};
