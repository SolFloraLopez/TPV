#include "GameStateMachine.h"

void GameStateMachine::changeState(GameState* state)
{
	delete stateStack.top();
	stateStack.pop();
	stateStack.push(state);
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
