#include "GameLogic.h"
#include "Collisions.h"
#include "Resources.h"
#include "Entity.h"

GameLogic::GameLogic(Transform *fighterTR, Transform *leftPaddleTR,
		Transform *rightPaddleTR) :
		Component(ecs::GameLogic), //
		fighterTR_(fighterTR), //
		leftPaddleTR_(leftPaddleTR), //
		rightPaddleTR_(rightPaddleTR), //
		scoreManager_(nullptr) //
{
}

GameLogic::~GameLogic() {
}

void GameLogic::init() {
	// scoreManager_ = GETCMP2(ecs::ScoreManager,ScoreManager);
	scoreManager_ = GETCMP1_(ScoreManager);
}

void GameLogic::update() {
	//// check for collision of ball with paddles
	//if (Collisions::collides(fighterTR_->getPos(), fighterTR_->getW(),
	//		fighterTR_->getH(), leftPaddleTR_->getPos(), leftPaddleTR_->getW(),
	//		leftPaddleTR_->getH())
	//		|| Collisions::collides(fighterTR_->getPos(), fighterTR_->getW(),
	//				fighterTR_->getH(), rightPaddleTR_->getPos(),
	//				rightPaddleTR_->getW(), rightPaddleTR_->getH())) {
	//	Vector2D v = fighterTR_->getVel();
	//	v.setX(-v.getX());
	//	fighterTR_->setVel(v * 1.2);
	//	game_->getAudioMngr()->playChannel(Resources::Paddle_Hit, 0);
	//}

	//// check if the back exit from sides
	//if (fighterTR_->getPos().getX() <= 0) {
	//	scoreManager_->setRightScore(scoreManager_->getRightScore() + 1);
	//	scoreManager_->setRunning(false);
	//	fighterTR_->setVel(Vector2D(0, 0));
	//	fighterTR_->setPos(
	//			Vector2D(game_->getWindowWidth() / 2 - 6,
	//					game_->getWindowHeight() / 2 - 6));

	//} else if (fighterTR_->getPos().getX() + fighterTR_->getW()
	//		>= game_->getWindowWidth()) {
	//	scoreManager_->setLeftScore(scoreManager_->getLeftScore() + 1);
	//	scoreManager_->setRunning(false);
	//	fighterTR_->setPos(
	//			Vector2D(game_->getWindowWidth() / 2 - 6,
	//					game_->getWindowHeight() / 2 - 6));
	//	fighterTR_->setVel(Vector2D(0, 0));
	//}
}

