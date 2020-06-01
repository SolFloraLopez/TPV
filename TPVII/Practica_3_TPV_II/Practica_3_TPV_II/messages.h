#pragma once
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctime>

namespace msg {

using msgSizeType = uint32_t;

enum MsgId : uint8_t {
	_CONNECTED, //
	_CONNECTION_REFUSED, //
	_CLIENT_DISCONNECTED, //
	_PLAYER_INFO, //
	_POSITION_INFO, //
	_START_REQ, //
	_START_GAME, //
	_PLAYER_HIT, //
	_FIGHTER_SHOOT, //
	_FIGHTERS_COLLIDE, //
	_PLAYER_NAME, //



	//
	_last_MsgId_
};

#pragma pack(push,1)

struct Message {
	Message(msgSizeType size, MsgId id) :
			size(size), senderClientId(0), id(id) {
	}
	Message(MsgId id) :
			Message(sizeof(Message), id) {
	}
	msgSizeType size;
	uint32_t senderClientId;
	MsgId id;
};

struct ConnectedMsg: Message {
	ConnectedMsg(int clientId) :
			Message(sizeof(ConnectedMsg), _CONNECTED), clientId(clientId) {
	}
	uint32_t clientId;
};

struct ClientDisconnectedMsg: Message {
	ClientDisconnectedMsg(uint32_t clientId) :
			Message(sizeof(ClientDisconnectedMsg), _CLIENT_DISCONNECTED), clientId(
					clientId) {
	}
	uint32_t clientId;
};

struct PositionInfoMsg : Message {
	PositionInfoMsg(double x, double y, double rotation) :
		Message(sizeof(PositionInfoMsg), _POSITION_INFO), x(x), y(y), rot(rotation) {
	}		
	double x;
	double y;
	double rot;
	//pasar la rotacion tambien y la pos como vector2 igual esta mejor
};

struct PlayerHitMsg : Message {
	PlayerHitMsg(uint8_t player) :
		Message(sizeof(PlayerHitMsg), _PLAYER_HIT), player(player) {
	}
	uint8_t player;
};

struct PlayerName : Message {
	PlayerName(const char* player) :
		Message(sizeof(PlayerName), _PLAYER_NAME) {
		strcpy_s(player_, 11, player);
	}
	char player_[11];
};

//crear mensajes para las balas
#pragma pack(pop)

}
