#pragma once

#include "Component.h"
#include "Transform.h"


class Gun : public Component {
public:
	Gun();
	Gun(SDL_Keycode space);
	virtual ~Gun();

	inline void setCtrlKeys(SDL_Keycode space) {
		space_ = space;
	}

	void init() override;
	void update() override;

private:
	SDL_Keycode space_;
	Transform* tr_;
};
