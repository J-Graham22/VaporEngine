#include <SDL.h>
#include <SDL_image.h>

#include "../GameObject.h"
#include "../TextureLoader.h"

GameObject::GameObject(const char* textureSheet, int x, int y) {
	objectTexture = TextureLoader::LoadTexture(textureSheet);

	xPos = x;
	yPos = y;
}

void GameObject::Update() {
	xPos++;
	yPos++;

	srcRect.h = 16;
	srcRect.w = 16;
	srcRect.x = 0;
	srcRect.y = 0;

	dstRect.x = xPos;
	dstRect.y = yPos;
	dstRect.w = srcRect.w * 2;
	dstRect.h = srcRect.h * 2;
}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objectTexture, &srcRect, &dstRect);
}
