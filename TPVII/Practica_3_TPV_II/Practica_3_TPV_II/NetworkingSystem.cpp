#include "NetworkingSystem.h"

#include "messages.h"
#include "Manager.h"

NetworkingSystem::NetworkingSystem() :
		System(ecs::_sys_NetWorking) {

}

NetworkingSystem::~NetworkingSystem() {
}

void NetworkingSystem::recieve(const msg::Message &msg) {
	if (msg.senderClientId == mngr_->getClientId()) {
		game_->getNetworking()->send(msg);
	}
}

void NetworkingSystem::update() {
	auto net = game_->getNetworking();
	msg::Message *msg = nullptr;

	while ((msg = net->recieve()) != nullptr) {
		switch (msg->id) {
		case msg::_PLAYER_INFO:
			mngr_->forwardMsg<msg::Message>(msg->senderClientId,
				msg::_PLAYER_INFO);
			break;
		case msg::_CLIENT_DISCONNECTED:
			mngr_->forwardMsg<msg::ClientDisconnectedMsg>(msg->senderClientId,
				static_cast<msg::ClientDisconnectedMsg*>(msg)->clientId);
			break;
		case msg::_POSITION_INFO: {
			msg::PositionInfoMsg* m = static_cast<msg::PositionInfoMsg*>(msg);
			mngr_->forwardMsg<msg::PositionInfoMsg>(msg->senderClientId, m->x,
				m->y, m->rot);
			break;
		}
		case msg::_START_REQ: {
			mngr_->forwardMsg<msg::Message>(msg->senderClientId,
				msg::_START_REQ);
			break;
		}
		case msg::_START_GAME: {
			msg::Message* m = static_cast<msg::Message*>(msg);
			mngr_->forwardMsg<msg::Message>(msg->senderClientId, msg::_START_GAME);
			break;
		}
		case msg::_PLAYER_HIT: {
			mngr_->forwardMsg<msg::PlayerHitMsg>(msg->senderClientId,
				static_cast<msg::PlayerHitMsg*>(msg)->player);
			break;
		}
		case msg::_FIGHTER_SHOOT:
		{
			mngr_->forwardMsg<msg::Message>(msg->senderClientId, msg::_FIGHTER_SHOOT);
			break;
		}
		case msg::_FIGHTERS_COLLIDE:
		{
			mngr_->forwardMsg<msg::Message>(msg->senderClientId, msg::_FIGHTERS_COLLIDE);
			break;
		}
		case msg::_PLAYER_NAME:
		{
			mngr_->forwardMsg<msg::PlayerName>(msg->senderClientId, static_cast<msg::PlayerName*>(msg)->player_);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

}
