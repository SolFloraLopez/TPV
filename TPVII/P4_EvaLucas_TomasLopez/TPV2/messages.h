#pragma once
#include <ctime>

class Entity;

namespace msg {

using msgType = std::size_t;

enum MsgId : msgType {
	_GAME_START, 
	_GAME_OVER,
	_FOOD_COLLISION,
	_NO_FOOD,

	//
	_last_MsgId_
};

struct Message {
	Message(MsgId id) : //game_start , game_over, player_win , add_reqs
			id(id) {
	}

	MsgId id;
};

struct FoodCollisionMsg : Message {
	FoodCollisionMsg(Entity* food) : Message(_FOOD_COLLISION), food(food) {}
	Entity* food;
};

//struct GhostCollisionMsg : Message {
//	GhostCollisionMsg(Entity* pacman, Entity* ghost) : Message(_GHOST_COLLISION),pacman(pacman), ghost(ghost) {}
//	Entity* pacman;
//	Entity* ghost;
//};


}
