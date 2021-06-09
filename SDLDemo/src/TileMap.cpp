#include "../TileMap.h"
#include "../Game.h"
#include "../ECS.h"
#include "../Components.h"
#include <fstream>

extern Manager manager;

TileMap::TileMap(std::string textureID, int mapScale, int tileSize) : textureID(textureID), mapScale(mapScale), tileSize(tileSize)  {
	scaledSize = mapScale * tileSize;
}

TileMap::~TileMap() {
	
}

void TileMap::LoadMap(std::string path, int sizeX, int sizeY) {
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	/*
	TODO: Check to see how to implement this system or create a different one that works with aseprite. Otherwise, it's dead code that only works with PyxelEdit, which I don't have
	*/

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(tile);
			srcY = atoi(&tile) * tileSize;
			mapFile.get(tile);
			srcX = atoi(&tile) * tileSize;
			AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
			mapFile.ignore();
		}
	}

	mapFile.ignore();

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(tile);
			if (tile == '1') {
				auto& tcol(manager.addEntity());
				tcol.addComponent<Collider>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
			mapFile.ignore();
		}
	}

	mapFile.close();
}

void TileMap::AddTile(int srcX, int srcY, int xPos, int yPos) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xPos, yPos, tileSize, mapScale, textureID);
	tile.addGroup(Game::groupMap);
}