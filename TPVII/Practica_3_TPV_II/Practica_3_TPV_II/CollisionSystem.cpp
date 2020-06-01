#include "CollisionSystem.h"

#include "Collisions.h"
#include "BulletsSystem.h"
#include "FighterInfo.h"
#include "GameCtrlSystem.h"
#include "Transform.h"
#include "Manager.h"

CollisionSystem::CollisionSystem() :
		System(ecs::_sys_Collision) {
}

CollisionSystem::~CollisionSystem() {
}

void CollisionSystem::update() {
	
	auto gameCtrlSys = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);

	if (gameCtrlSys->getState() != GameCtrlSystem::RUNNING)
		return;


	bool roundOver = false;

	Transform* fgTR0 = mngr_->getGroupEntities(ecs::_grp_Fighters)[0]->getComponent<Transform>(ecs::Transform);
	Transform* fgTR1 = mngr_->getGroupEntities(ecs::_grp_Fighters)[1]->getComponent<Transform>(ecs::Transform);

	if(Collisions::collidesWithRotation(fgTR0->position_, fgTR0->width_,
		fgTR0->height_, fgTR0->rotation_, fgTR1->position_, fgTR1->width_,
		fgTR1->height_, fgTR1->rotation_))
	{
		roundOver = true;
		mngr_->send<msg::Message>(msg::_FIGHTERS_COLLIDE);
	}

	for (auto &f : mngr_->getGroupEntities(ecs::_grp_Fighters)) {
		auto fTR = f->getComponent<Transform>(ecs::Transform);

		for (auto &b : mngr_->getGroupEntities(ecs::_grp_Bullets)) {
			if (!b->isActive())
				continue;

			auto bTR = b->getComponent<Transform>(ecs::Transform);

			if (Collisions::collidesWithRotation(bTR->position_, bTR->width_,
					bTR->height_, bTR->rotation_, fTR->position_, fTR->width_,
					fTR->height_, fTR->rotation_)) {

				roundOver = true;
				auto id = f->getComponent<FighterInfo>(ecs::FighterInfo)->fighterId;
				//mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->onFighterDeath(id);

				mngr_->send<msg::PlayerHitMsg>(id);
			}
		}
	}

	if ( roundOver )
		mngr_->getSystem<BulletsSystem>(ecs::_sys_Bullets)->disableAll();
}

