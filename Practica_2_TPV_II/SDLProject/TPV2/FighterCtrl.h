#pragma once

#include "Component.h"
#include "Transform.h"

class FighterCtrl : public Component {
public:
	FighterCtrl();
	FighterCtrl(SDL_Keycode up, SDL_Keycode right, SDL_Keycode left);
	virtual ~FighterCtrl();

	inline void setCtrlKeys(SDL_Keycode up, SDL_Keycode right,
		SDL_Keycode left) {
		up_ = up;
		right_ = right;
		left_ = left;
	}

	void init() override;
	void update() override;

private:
	SDL_Keycode up_;
	SDL_Keycode right_;
	SDL_Keycode left_;
	Transform* tr_;
};

