#include "GameStateMachine.h"

void GameStateMachine::changeState(GameState* state)
{
	popState();
	pushState(state);
}

void GameStateMachine::pushState(GameState* state)
{
	stateStack.push(state);
}

GameState* GameStateMachine::currentState()
{
	return stateStack.top();
}

void GameStateMachine::popState()
{
	delete stateStack.top();
	stateStack.pop();
}

void GameStateMachine::setFlag(string thisFlag) 
{
	flag = thisFlag;
}

string GameStateMachine::getFlag()
{
	return flag;
}
