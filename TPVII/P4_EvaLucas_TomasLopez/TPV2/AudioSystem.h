#pragma once

#include "System.h"


class AudioSystem : public System {
public:

	AudioSystem();

	void init() override;
	void update() override;
	void recieve(const msg::Message& msg) override;

	// TODO: these methods should go private


private:
		

};
#pragma once
