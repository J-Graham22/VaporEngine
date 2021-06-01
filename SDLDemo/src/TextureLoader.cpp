#include "../TextureLoader.h"

SDL_Texture* TextureLoader::LoadTexture(const char* fileName) {
	SDL_Texture* texture = IMG_LoadTexture(Game::renderer, fileName);
	return texture;
}

void TextureLoader::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip spriteFlip) {
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dst, NULL, NULL, spriteFlip);
}