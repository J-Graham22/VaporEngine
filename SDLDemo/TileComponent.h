#pragma once

#include "ECS.h"
#include "Components.h"
#include "AssetManager.h"
#include <SDL.h>

class TileComponent : public Component {
public:
	
	SDL_Texture* texture;
	SDL_Rect srcRect, dstRect;
	Vector2D position;

	TileComponent() = default;

	~TileComponent() {
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xPos, int yPos, int tileSize, int tileScale, std::string id) {
		texture = Game::assets->GetTexture(id);

		position.x = xPos;
		position.y = yPos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tileSize;

		dstRect.x = xPos;
		dstRect.y = yPos;
		dstRect.w = dstRect.h = tileSize * tileScale;
	}

	void update() override {
		dstRect.x = position.x - Game::camera.x;
		dstRect.y = position.y - Game::camera.y;
	}

	void draw() override {
		TextureLoader::Draw(texture, srcRect, dstRect, SDL_FLIP_NONE);
	}

};
