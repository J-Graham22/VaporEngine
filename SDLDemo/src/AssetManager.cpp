#include "../AssetManager.h"
#include "../Components.h"

AssetManager::AssetManager(Manager* manager) : manager(manager) {

}

AssetManager::~AssetManager() {}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D velocity, int range, int speed, std::string id) {
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 16, 16, 1);
	//Obviously you'd change this to a real texture for a projectile, but for now I'm just going to use the small enemy
	projectile.addComponent<SpriteComponent>(id, false);
	projectile.addComponent<ProjectileComponent>(range, speed, velocity);
	projectile.addComponent<Collider>("projectile");
	projectile.addGroup(Game::groupProjectiles);

}

void AssetManager::AddTexture(std::string id, const char* filePath) {
	textures.emplace(id, TextureLoader::LoadTexture(filePath));
}

SDL_Texture* AssetManager::GetTexture(std::string id) {
	return textures[id];
}

void AssetManager::AddFont(std::string id, std::string path, int fontSize) {
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}
TTF_Font* AssetManager::GetFont(std::string id) {
	return fonts[id];
}
