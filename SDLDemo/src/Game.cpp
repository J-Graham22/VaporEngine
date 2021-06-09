#include <iostream>
#include <sstream>

#include "../Game.h"
#include "../TextureLoader.h"
#include "../TileMap.h"
#include "../Components.h"
#include "../Vector2D.h"
#include "../CollisionMath.h"
#include "../AssetManager.h"


TileMap* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;



SDL_Rect Game::camera = { 0,0, Game::windowWidth, Game::windowHeight };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());

auto& ground(manager.addEntity());
auto& leftWall(manager.addEntity());
auto& rightWall(manager.addEntity());
auto& ceiling(manager.addEntity());

auto& label(manager.addEntity());

Game::Game() {
	
}


Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		//Output message to tell us SDL has successfully initialized
		std::cout << "Successfully initialized!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		//Output message to tell us that the window has been successfully created
		if (window) {
			std::cout << "Window created!" << std::endl;
		}

		//Output message to tell us that the renderer has successfully been created
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}

	if (TTF_Init()) {
		std::cout << "Error : SDL_TTF not initialized." << std::endl;
	}

	assets->AddTexture("player","SimpleHero.png");
	assets->AddTexture("obstacle","BasicTile.png");
	assets->AddTexture("projectile", "projectile.png");

	assets->AddFont("04b", "04B_19_.TTF", 16);

	//Would use for the map
//	assets->AddTexture("terrain", "terrain file path");

	//ADDING ENTITIES TO THE SCENE
	
	//map = new TileMap("terrain", mapSize, tileScale);

	//Would load a map in from here
//	map->LoadMap("insert whatever the path to the imported map would be", { number of tiles in x direction }, { number of tiles in y direction });

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<Gravity>();
//	player.getComponent<Gravity>().setFallSpeed(0.01f);
	player.addComponent<Collider>("player");
	player.addGroup(groupPlayer);

	ground.addComponent<TransformComponent>(0.0f, 600.0f, 40, 800, 1);
	ground.addComponent<SpriteComponent>("obstacle", false);
	ground.addComponent<Collider>("floor");
	ground.addGroup(groupMap);
	ground.addGroup(groupColliders);

	leftWall.addComponent<TransformComponent>(0.0f, 0.0f, 640, 40, 1);
	leftWall.addComponent<SpriteComponent>("obstacle", false);
	leftWall.addComponent<Collider>("floor");
	leftWall.addGroup(groupMap);
	leftWall.addGroup(groupColliders);

	rightWall.addComponent<TransformComponent>(760.0f, 0.0f, 640, 40, 1);
	rightWall.addComponent<SpriteComponent>("obstacle", false);
	rightWall.addComponent<Collider>("floor");
	rightWall.addGroup(groupMap);
	rightWall.addGroup(groupColliders);

	ceiling.addComponent<TransformComponent>(0.0f, 0.0f, 40, 800, 1);
	ceiling.addComponent<SpriteComponent>("obstacle", false);
	ceiling.addComponent<Collider>("floor");
	ceiling.addGroup(groupMap);
	ceiling.addGroup(groupColliders);

	SDL_Color white = { 255, 255, 255, 255 };
	label.addComponent<UILabel>(10, 10, "testing testing 1 2 3", "04b", white);

	assets->CreateProjectile(Vector2D(60, 60), Vector2D(1, 0), 200, 2, "projectile", "projectile");
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayer));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

void Game::handleEvents() {

	SDL_PollEvent(&event);

	switch (event.type) 
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {
	SDL_Rect playerCollider = player.getComponent<Collider>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	std::stringstream stream;
	stream << "Player position: " << playerPos;
	label.getComponent<UILabel>().SetLabelText(stream.str(), "04b");

	manager.refresh();
	manager.update();

	for (auto& c : colliders) {
		
			SDL_Rect cCollider = c->getComponent<Collider>().collider;

			if (CollisionMath::AABB(cCollider, playerCollider)) {
				player.getComponent<TransformComponent>().position = playerPos;
				//player.getComponent<TransformComponent>().velocity.y = 0;
			}
		
	
	}

	for (auto& pr : projectiles) {
		if (CollisionMath::AABB(player.getComponent<Collider>().collider, pr->getComponent<Collider>().collider) && pr->getComponent<Collider>().tag == "projectile" && projectiles.size() <= 3) {
			//The projectile has successfully hit
			std::cout << "Hit player with tag: "<< pr->getComponent<Collider>().tag << std::endl;
			pr->destroy();
		}
	}

	if (projectiles.empty()) {
		assets->CreateProjectile(Vector2D(60, 60), Vector2D(1, 0), 200, 2, "projectile", "projectile");
	}

	if (playerPos.y < 200) {
		SDL_Color green = { 100, 255, 100, 255 };
		label.getComponent<UILabel>().SetTextColor(green);
	}
	else if (playerPos.y < 400) {
		SDL_Color blue = { 100, 100, 200, 255 };
		label.getComponent<UILabel>().SetTextColor(blue);
	}
	else {
		SDL_Color red = { 255, 100,100,255 };
		label.getComponent<UILabel>().SetTextColor(red);
	}

//	camera.x = player.getComponent<TransformComponent>().position.x - 400;
	//camera.y = player.getComponent<TransformComponent>().position.y - 320;

	//if (camera.x < -camera.w) {
	//	camera.x = -camera.w;
	//}

	//if (camera.y < -camera.h) {
	//	camera.y = -camera.h;
	//}

	//if (camera.x > camera.w) {
	//	camera.x = camera.w;
	//}

	//if (camera.y > camera.h) {
	//	camera.y = camera.h;
	//}

//	camera.y--;

	if (camera.y + Game::windowHeight < player.getComponent<TransformComponent>().position.y) {
		std::cout << "Player has died" << std::endl;
	}

	//for (auto& t : tiles) {
	//	if (camera.y + Game::windowHeight < t->getComponent<TransformComponent>().position.y) {
	//		
	//	//	t->destroy();
	//		Game::addObstacle();
	//	}
	//}

	

	//Vector2D playerVelocity = player.getComponent<TransformComponent>().velocity;
	//int playerSpeed = player.getComponent<TransformComponent>().speed;

	//for (auto t : tiles) {
	//	/*
	//	NOTE: this is different from what was "supposed" to be here. The two lines below are what were there before:

	//	t->getComponent<TileComponent>().dstRect.x += -(playerVelocity.x * playerSpeeed);
	//	t->getComponent<TileComponent>().dstRect.y += -(playerVelocity.y * playerSpeed);
	//	
	//	This was throwing an exception because things are going into the tiles group that do not have the Tile Component but ought to behave as tiles should.
	//	This solution is working for now and seems more modular, but it remains to be seen if collision is working with this implementation. */

	//	t->getComponent<TransformComponent>().position.x += -(playerVelocity.x * playerSpeed);
	//	t->getComponent<TransformComponent>().position.y += -(playerVelocity.y * playerSpeed);
	//}

	
}



void Game::render() {
	SDL_RenderClear(renderer);
	for (auto& t : tiles) {
		t->draw();
	}

	for (auto& c : colliders) {
		c->draw();
	}

	for (auto& t : players) {
		t->draw();
	}

	for (auto& pr : projectiles) {
		pr->draw();
	}

	label.draw();
	
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game closed" << std::endl;
}



void Game::addObstacle() {
	//Width between each side should be 80 pixels

	//Mid, Left, or Right

	int midX = 360;
	int leftX = 40;
	int rightX = 680;

	//Replace with std::array??
	int possibleX[3] = { midX, leftX, rightX };

	int random = rand() % 3;

	int starterX = possibleX[random];

	auto& obstacleLeft(manager.addEntity());
	obstacleLeft.addComponent<TransformComponent>(0, -50, 40, starterX, 1);
	obstacleLeft.addComponent<SpriteComponent>("BasicTile.png");
	obstacleLeft.addComponent<Collider>("obstacle-left");
	obstacleLeft.addGroup(groupMap);

	auto& obstacleRight(manager.addEntity());
	obstacleRight.addComponent<TransformComponent>(starterX + 80, -50, 40, Game::windowWidth - (starterX + 80), 1);
	obstacleRight.addComponent<SpriteComponent>("BasicTile.png");
	obstacleRight.addComponent<Collider>("obstacle-right");
	obstacleRight.addGroup(groupMap);

}

void Game::shoot() {
	int direction;
	if (player.getComponent<SpriteComponent>().spriteFlip == SDL_FLIP_NONE) {
		direction = 1;
	}
	else {
		direction = -1;
	}
	assets->CreateProjectile(player.getComponent<TransformComponent>().position, Vector2D(direction, 0), 200, 2, "projectile", "player projectile");
}



