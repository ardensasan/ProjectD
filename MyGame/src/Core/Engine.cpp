#include "Engine.h"
#include "TextureManager.h"
#include "MapParser.h"
Engine* Engine::instance = nullptr;
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
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_PNG) != 0) {
		SDL_Log("Failed to initialize SDL %s", SDL_GetError());
		bIsRunning = false;
	}
	else {
		window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 576, 0);
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
				MapParser::GetInstance()->Load();
				bIsRunning = true;
			}
		}
	}
}
void Engine::Events() {

}
void Engine::Update() {

}
void Engine::Render() {

}
void Engine::Clean() {
	TextureManager::GetInstance()->Clean();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = nullptr;
	renderer = nullptr;
}

void Engine::Quit() {
	bIsRunning = false;
}