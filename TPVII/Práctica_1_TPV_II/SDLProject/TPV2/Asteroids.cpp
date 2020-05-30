#include "SDL_macros.h"
#include "Asteroids.h"
#include <assert.h>

#include "GameCtrl.h"
#include "GameLogic.h"
#include "InputHandler.h"
#include "FighterCtrl.h"
#include "FighterMotion.h"
#include "AsteroidsMotion.h"
#include "AsteroidsViewer.h"
#include "BulletsMotion.h"
#include "BulletsViewer.h"
#include "Gun.h"
#include "FighterViewer.h"
#include "Health.h"
#include "ScoreManager.h"
#include "ScoreViewer.h"
#include "Transform.h"
#include "SDLGame.h"

#include "SDL_macros.h"

using namespace std;

Asteroids::Asteroids() :
	game_(nullptr), //
	entityManager_(nullptr), //
	exit_(false) {
	initGame();
}

Asteroids::~Asteroids() {
	closeGame();
}

void Asteroids::initGame() {

	game_ = SDLGame::init("Ping Pong", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	entityManager_ = new EntityManager(game_);

	

	Entity* asteroids = entityManager_->addEntity();
	asteroidPool_ = asteroids->addComponent<AsteroidPool>();
	asteroids->addComponent<AsteroidsMotion>();
	asteroids->addComponent<AsteroidsViewer>();

	Entity* bullets = entityManager_->addEntity();
	bulletsPool_ = bullets->addComponent<BulletsPool>();
	bullets->addComponent<BulletsMotion>();
	bullets->addComponent<BulletsViewer>();

	Entity* fighter = entityManager_->addEntity();
	Transform* fighterTR = fighter->addComponent<Transform>();
	fighter->addComponent<FighterViewer>();
	health_ = fighter->addComponent<Health>(3);
	fighter->addComponent<FighterMotion>();
	fighter->addComponent<FighterCtrl>();
	fighter->addComponent<Gun>(bulletsPool_);
	fighterTR->setPos(game_->getWindowWidth() / 2 - 6,
		game_->getWindowHeight() / 2 - 6);
	fighterTR->setWH(50, 50);


	Entity* gameManager = entityManager_->addEntity();
	gameManager->addComponent<ScoreManager>(1);
	gameManager->addComponent<GameLogic>(fighterTR, asteroidPool_, bulletsPool_, health_);
	gameManager->addComponent<ScoreViewer>();
	gameManager->addComponent<GameCtrl>(asteroidPool_, health_);
}

void Asteroids::closeGame() {
	delete entityManager_;
}

void Asteroids::start() {
	exit_ = false;

	while (!exit_) {
		Uint32 startTime = game_->getTime();

		handleInput();
		update();
		render();

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void Asteroids::stop() {
	exit_ = true;
}

void Asteroids::handleInput() {

	InputHandler* ih = InputHandler::instance();

	ih->update();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(SDLK_ESCAPE)) {
			exit_ = true;
		}

		if (ih->isKeyDown(SDLK_f)) {
			int flags = SDL_GetWindowFlags(game_->getWindow());
			if (flags & SDL_WINDOW_FULLSCREEN) {
				SDL_SetWindowFullscreen(game_->getWindow(), 0);
			}
			else {
				SDL_SetWindowFullscreen(game_->getWindow(),
					SDL_WINDOW_FULLSCREEN);
			}
		}
	}

}

void Asteroids::update() {
	entityManager_->update();
}

void Asteroids::render() {
	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(game_->getRenderer());

	entityManager_->draw();

	SDL_RenderPresent(game_->getRenderer());
}

