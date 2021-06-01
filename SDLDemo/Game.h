#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <vector>
#include <iostream>

class AssetManager;
class Collider;

class Game {
public:
	Game();
	~Game();

	static const int windowHeight = 640;
	static const int windowWidth = 800;

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	inline bool running() { return isRunning; };
	void render();
	void clean();
	void addObstacle();


	static SDL_Renderer* renderer;
	static SDL_Event event;
//	static std::vector<Collider*> colliders;
	static AssetManager* assets;
	static bool isRunning;
	static SDL_Rect camera;
	enum groupLabels : std::size_t {
		groupMap,
		groupPlayer,
		groupColliders,
		groupEnemies,
		groupProjectiles
	};
private:
	SDL_Window* window;
};
