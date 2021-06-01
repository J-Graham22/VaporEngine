#pragma once
#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component {
private:

public:
	Vector2D position;
	Vector2D velocity;

	int height = 16;
	int width = 16;
	int scale = 1;

	//May be changed later
	int speed = 3;

	TransformComponent() {
		position.Zero();
	}

	TransformComponent(int s) {
		//Center of the screen
		position.x = 400;
		position.y = 320;
		scale = s;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, int s) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = s;
	}

	void init() override {
		velocity.Zero();
	}

	void update() override {
		//For any updates to the entities position
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;


	}

};
