#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	/*
	TODO : Use vectors to change animations instead of keyboard inputs? Maybe, maybe not
	*/

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				sprite->play("Walk");
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->play("Walk");
				sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->play("Walk");
				sprite->spriteFlip = SDL_FLIP_NONE;
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->play("Walk");
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
			case SDLK_SPACE:
				Game::shoot();
			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				sprite->play("Idle");
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->play("Idle");
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->play("Idle");
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				sprite->play("Idle");
				break;
			default:
				break;
			}
		}
	}
};
