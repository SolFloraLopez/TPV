#pragma once
#include "GameState.h"
#include <stack>

class GameStateMachine 
{
private:
	stack<GameState*> stateStack;
	string flag = "";
public:
	~GameStateMachine();
	GameState* currentState() { return stateStack.top(); };
	void pushState(GameState* state) { stateStack.push(state); };
	void changeState(GameState* state) { popState(); pushState(state);};
	void popState() { delete stateStack.top(); stateStack.pop(); };
	void setFlag(string thisFlag) { flag = thisFlag; };
	string getFlag() { return flag; };
};
