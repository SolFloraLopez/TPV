#pragma once
#include "Component.h"

struct GameState : Component {
	GameState() :
		state_(Parado) //
	{
	}

	enum states {Parado,Terminado,EnCurso};
	unsigned int state_;
};
