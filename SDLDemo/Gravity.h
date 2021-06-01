#pragma once

#include "ECS.h"
#include "Components.h"
#include "Game.h"

class Gravity : public Component {
private:
	float fallSpeed = 0.0f;

public:
	TransformComponent* transform;
	

	float getFallSpeed() {
		return fallSpeed;
	}	

	void setFallSpeed(float speed) {
		fallSpeed = speed;
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override {
		transform->velocity.y += fallSpeed;
	}
};

