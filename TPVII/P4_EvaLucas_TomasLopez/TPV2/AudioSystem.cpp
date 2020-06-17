#include "AudioSystem.h"

#include "System.h"
#include "Entity.h"
#include "FoodPool.h"
#include "GameState.h"
#include "Manager.h"
#include "SDLGame.h"
#include "SDL_macros.h"

AudioSystem::AudioSystem() :
	System(ecs::_sys_Audio) {}


void AudioSystem::init() {
	game_->getAudioMngr()->playMusic(Resources::PacMan_Intro);
}

void AudioSystem::update() {

}

void AudioSystem::recieve(const msg::Message& msg) {
	switch (msg.id)
	{
	case msg::_GAME_START: {
		game_->getAudioMngr()->haltMusic();
		break;
	}
	case msg::_GAME_READY: {
		game_->getAudioMngr()->haltMusic();
		game_->getAudioMngr()->playMusic(Resources::PacMan_Intro);

		break;
	}
	case msg::_GAME_OVER: {
		game_->getAudioMngr()->haltMusic();
		game_->getAudioMngr()->playChannel(Resources::PacMan_Death, 0);
		break;
	}
	case msg::_FOOD_COLLISION: {
		game_->getAudioMngr()->playChannel(Resources::PacMan_Eat, 0);
		break;
	}
	case msg::_NO_FOOD: {
		game_->getAudioMngr()->haltMusic();
		game_->getAudioMngr()->playChannel(Resources::PacMan_Won, 0);
		break;
	}
	default:
		break;
	}
}

