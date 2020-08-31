#include "GameStateMachine.h"

GameStateMachine::~GameStateMachine() {
	while (!stateStack.empty())
	{
		delete stateStack.top();
		stateStack.pop();
	}
}

