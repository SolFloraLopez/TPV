#include "ScoreManager.h"

ScoreManager::ScoreManager() :
		ScoreManager(5) {
}

ScoreManager::ScoreManager(int rounds) :
		Component(ecs::ScoreManager), //
		stopped_(true), //
		finished_(false), //
		Score_(0)//
{
}

ScoreManager::~ScoreManager() {
}

