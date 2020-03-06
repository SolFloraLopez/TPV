#pragma once

#include "Component.h"
#include "Transform.h"

class AsteroidsMotion : public Component {
public:
	AsteroidsMotion();
	virtual ~AsteroidsMotion();
	void init() override;
	void update() override;
private:
	Transform* tr_;
};

