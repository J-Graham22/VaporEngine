#pragma once
#include <string>

class TileMap {
public:
	TileMap(std::string textureID, int mapScale, int tileSize);
	~TileMap();

	void AddTile(int srcX, int srcY, int xPos, int yPos);
	void LoadMap(std::string path, int sizeX, int sizeY);
private:
	std::string textureID;
	int mapScale;
	int tileSize;
	int scaledSize;
};
