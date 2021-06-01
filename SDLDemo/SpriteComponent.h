#pragma once
#include "Components.h"
#include "TextureLoader.h"
#include "Animation.h"
#include "AssetManager.h"
#include <SDL.h>
#include <map>

class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, dstRect;

	bool animated = false;
	int frames = 0;
	int millisecondDelayBetweenFrames = 100;
public:

	int animationIndex = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;

	SpriteComponent(std::string id) {
		setTexture(id);
	}

	SpriteComponent(std::string id, bool isAnimated) {
		animated = isAnimated;

		//This seems like a bad idea to put implementation of specific animations here\
		//Should allocate out to a different function call for better modularity
		Animation idle = Animation(0, 15, 100);
		Animation walk = Animation(1, 2, 100);
		Animation jump = Animation(2, 1, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);
		animations.emplace("Jump", jump);

		play("Idle");

		setTexture(id);
	}

	~SpriteComponent() {}

	void setTexture(std::string id) {
		texture = Game::assets->GetTexture(id);
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override {
		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / millisecondDelayBetweenFrames) % frames);
		}

		srcRect.y = animationIndex * transform->height;

		dstRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		dstRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
		dstRect.w = transform->width * transform->scale;
		dstRect.h = transform->height * transform->scale;
	}

	void draw() override {
		TextureLoader::Draw(texture, srcRect, dstRect, spriteFlip);
	}

	void play(const char* animationName) {
		frames = animations[animationName].frames;
		animationIndex = animations[animationName].index;
		millisecondDelayBetweenFrames = animations[animationName].speed;
	}
};
