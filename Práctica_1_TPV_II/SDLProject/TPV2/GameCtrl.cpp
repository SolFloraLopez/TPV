#include "GameCtrl.h"

#include "Entity.h"
#include "InputHandler.h"

GameCtrl::GameCtrl(AsteroidPool* asteroidPool, Health* health) :
		Component(ecs::GameCtrl), //
	    asteroidPool_(asteroidPool), //
	    health_(health), //
		scoreManager_(nullptr) //
{
}

GameCtrl::~GameCtrl() {
}

void GameCtrl::init() {
	scoreManager_ = GETCMP1_(ScoreManager);
}

void GameCtrl::update() {

	if (InputHandler::instance()->keyDownEvent()) {
		if (scoreManager_->isStopped()) {
			asteroidPool_->generateAsteroids(10);
			scoreManager_->setStopped(false);

			// rest the score if the game is over
			if (scoreManager_->isFinished()) {
				scoreManager_->setScore(0);
				health_->resetHealth();
			}
		}
	}
}

void GameCtrl::draw() {

	if (scoreManager_->isStopped()) {
		Texture *hitanykey = game_->getTextureMngr()->getTexture(
				Resources::PresAnyKey);
		hitanykey->render(
				game_->getWindowWidth() / 2 - hitanykey->getWidth() / 2,
				game_->getWindowHeight() - hitanykey->getHeight() - 50);
	}

	// game over message when game is over
	if (scoreManager_->isFinished()) {
		Texture* gameOver;

		if(health_->getHealth() <= 0) gameOver = game_->getTextureMngr()->getTexture(Resources::GameOverWon);
		else gameOver = game_->getTextureMngr()->getTexture(Resources::GameOverLost);
		gameOver->render(game_->getWindowWidth() / 2 - gameOver->getWidth() / 2,
				game_->getWindowHeight() - gameOver->getHeight() - 150);
	}
}
