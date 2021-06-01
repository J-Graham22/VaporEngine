#pragma once

#include "Game.h"

class TextureLoader {
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip spriteFlip);
private:
};
