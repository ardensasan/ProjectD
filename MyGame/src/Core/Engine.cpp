#include "Engine.h"
#include "TextureManager.h"
#include "MapParser.h"
#include "Input.h"
#include "Player.h"
#include "Camera.h"
#include "CollisionHandler.h"
Engine* Engine::instance = nullptr;
Player* player;
Engine::Engine() {
	bIsRunning = false;
	window = nullptr;
	renderer = renderer;
}
Engine* Engine::GetInstance() {
	if (instance == nullptr)
		instance = new Engine();
	return instance;
}

void Engine::Init() {
	screenWidth = 1024;
	screenHeight = 576;
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_PNG) != 0) {
		SDL_Log("Failed to initialize SDL %s", SDL_GetError());
		bIsRunning = false;
	}
	else {
		window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, 0);
		if (window == nullptr) {
			SDL_Log("Failed to create window %s", SDL_GetError());
			bIsRunning = false;
		}
		else {
			renderer = SDL_CreateRenderer(window, -1, (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
			if (window == nullptr) {
				SDL_Log("Failed to create renderer %s", SDL_GetError());
				bIsRunning = false;
			}
			else {
				TextureManager::GetInstance()->Load("player_idle","assets/Player/Idle.png");
				TextureManager::GetInstance()->Load("player_fall", "assets/Player/Fall.png");
				TextureManager::GetInstance()->Load("player_jump", "assets/Player/Jump.png");
				TextureManager::GetInstance()->Load("player_run", "assets/Player/Run.png");
				Camera::GetInstance()->Set(screenWidth, screenHeight);
				if (!MapParser::GetInstance()->Load()) {
					bIsRunning = false;
					MapParser::GetInstance()->Clean();
				}
				else {
					player = new Player("player_idle", 32, 32);
					bIsRunning = true;
				}
				
			}
		}
	}
}
void Engine::Events() {
	Input::GetInstance()->Listen();
}
void Engine::Update() {
	player->Update();
	MapParser::GetInstance()->GetMapLayers();
}
void Engine::Render() {
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 50);
	SDL_RenderClear(renderer);
	MapParser::GetInstance()->Render();
	player->Draw();
	SDL_RenderPresent(renderer);
}
void Engine::Clean() {
	TextureManager::GetInstance()->Clean();
	MapParser::GetInstance()->Clean();
	CollisionHandler::GetInstance()->Clean();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = nullptr;
	renderer = nullptr;
}

void Engine::Quit() {
	bIsRunning = false;
}