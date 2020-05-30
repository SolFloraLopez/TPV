#include "Asteroids.h"

#include "Manager.h"
#include "GameCtrlSystem.h"
#include "FighterSystem.h"
#include "FighterGunSystem.h"
#include "AsteroidsSystem.h"
#include "BulletsSystem.h"
#include "RenderSystem.h"
#include "CollisionSystem.h"

#include "InputHandler.h"
#include "Health.h"
#include "Transform.h"


using namespace std;

Asteroids::Asteroids() :
	game_(nullptr), //
	mngr_(nullptr), //
	exit_(false) {
	initGame();
}

Asteroids::~Asteroids() {
	closeGame();
}

void Asteroids::initGame() {

	game_ = SDLGame::init("Ping Pong", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	mngr_ = new Manager(game_);

	AsteroidPool::init(10);
	BulletsPool::init(10);

	renderSystem_ = mngr_->addSystem<RenderSystem>();
	collisionSystem_ = mngr_->addSystem<CollisionSystem>();
	gameCtrlSystem_ = mngr_->addSystem<GameCtrlSystem>();
	fighterSystem_ = mngr_->addSystem<FighterSystem>();
	fighterGunSystem_ = mngr_->addSystem<FighterGunSystem>();
	asteroidsSystem_ = mngr_->addSystem<AsteroidsSystem>();
	bulletsSystem_ = mngr_->addSystem<BulletsSystem>();
}

void Asteroids::closeGame() {
	delete mngr_;
}

void Asteroids::start() {
	exit_ = false;
	auto ih = InputHandler::instance();
	while (!exit_) {
		SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
		SDL_RenderClear(game_->getRenderer());
		Uint32 startTime = game_->getTime();

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

		mngr_->refresh();
		gameCtrlSystem_->update();
		renderSystem_->update(); 
		collisionSystem_->update();
		fighterSystem_->update();
		fighterGunSystem_->update();
		asteroidsSystem_->update();
		bulletsSystem_->update();
		
		
			Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
		SDL_RenderPresent(game_->getRenderer());
	}	
}

void Asteroids::stop() {
	exit_ = true;
}

