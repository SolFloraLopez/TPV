#pragma once

#include "Component.h"
#include "Transform.h"

class BulletsMotion : public Component {
public:
	BulletsMotion();
	virtual ~BulletsMotion();
	void init() override;
	void update() override;
private:
	Transform* tr_;
};

