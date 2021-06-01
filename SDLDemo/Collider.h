#pragma once

#include <string>
#include <sdl.h>
#include "Components.h"
#include "TextureLoader.h"

class Collider : public Component {
public:
	SDL_Rect collider;
	std::string tag;

	SDL_Texture* texture;
	SDL_Rect srcRect, dstRect;

	TransformComponent* transform;

	Collider(std::string t) {
		tag = t;
	}

	Collider(std::string t, int xPos, int yPos, int size) {
		tag = t;
		collider.x = xPos;
		collider.y = yPos;
		collider.h = collider.w = size;
	}

	void init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		//This would be for seeing colliders if we wanted to
		texture = TextureLoader::LoadTexture("");
		srcRect = { 0, 0, 16, 16 };
		dstRect = { collider.x, collider.y, collider.w, collider.h };
	}

	void update() override {
		//Not sure if this if statement is very relevant for my project
		if (tag != "terrain") {
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}

		dstRect.x = collider.x - Game::camera.x;
		dstRect.y = collider.y - Game::camera.y;
	}

	void draw() override {
		TextureLoader::Draw(texture, srcRect, dstRect, SDL_FLIP_NONE);
	}


};
