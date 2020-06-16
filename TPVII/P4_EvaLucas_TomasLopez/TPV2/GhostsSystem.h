#pragma once

#include "System.h"
#include <SDL.h>

class GhostsSystem: public System {
public:
	GhostsSystem();
	void init() override;
	void update() override;

	void recieve(const msg::Message& msg) override;

	// TODO: these methods should go private
	
private:
	Uint32 lastTimeAdded_;
	int maxGhosts_;
	int numOfGhosts_;

	void onCollisionWithPacMan(Entity* e);
	void addGhosts(std::size_t n);
	void disableAll();

};

