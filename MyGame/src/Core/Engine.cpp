#include "Engine.h"
#include "TextureManager.h"
#include "MapParser.h"
#include "Input.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include "ObjectFactory.h"
#include "Timer.h"
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
				//load player assets
				TextureManager::GetInstance()->Load("player_idle","assets/Player/Idle.png");
				TextureManager::GetInstance()->Load("player_fall", "assets/Player/Fall.png");
				TextureManager::GetInstance()->Load("player_jump", "assets/Player/Jump.png");
				TextureManager::GetInstance()->Load("player_run", "assets/Player/Run.png");
				//load fruit assets
				TextureManager::GetInstance()->Load("Apple", "assets/Items/Fruits/Apple.png");
				TextureManager::GetInstance()->Load("Banana", "assets/Items/Fruits/Banana.png");
				TextureManager::GetInstance()->Load("Cherry", "assets/Items/Fruits/Cherry.png");
				TextureManager::GetInstance()->Load("Kiwi", "assets/Items/Fruits/Kiwi.png");
				Camera::GetInstance()->Set(screenWidth, screenHeight);
				if (!MapParser::GetInstance()->Load()) {
					bIsRunning = false;
					MapParser::GetInstance()->Clean();
				}
				else {
					staticObjectList.clear();
					movingObjectList.clear();
					std::vector<ObjectProperty> objectPropertyList;
					objectPropertyList = MapParser::GetInstance()->GetStaticObjects();
					std::vector<ObjectProperty>::iterator it;
					for (it = objectPropertyList.begin();it != objectPropertyList.end();it++)
						staticObjectList.push_back(ObjectFactory::GetInstance()->CreateObject(*it));
					objectPropertyList.clear();
					objectPropertyList = MapParser::GetInstance()->GetMovingObjects();
					for (it = objectPropertyList.begin();it != objectPropertyList.end();it++) {
						if (it->type == "Player")
							player = ObjectFactory::GetInstance()->CreateObject(*it);
						else
							movingObjectList.push_back(ObjectFactory::GetInstance()->CreateObject(*it));
					}
					objectPropertyList.clear();
					bIsRunning = true;
				}
				
			}
		}
	}
}
void Engine::Events() {
	Input::GetInstance()->Listen();
}

int aw = 0;
void Engine::Update() {
	aw++;
	float dt = Timer::GetInstance()->GetDeltaTime();
	std::vector<GameObject*>::iterator it;
	player->Update(dt);
	for (it = staticObjectList.begin();it != staticObjectList.end();it++) {
		if ((*it)->CheckCollisionToPlayer(player->GetCollider())) {
			it = staticObjectList.erase(it);
			if (it >= staticObjectList.end())
				break;
		}
		(*it)->Update(dt);
	}

	for (it = movingObjectList.begin();it != movingObjectList.end();it++)
		(*it)->Update(dt);
	MapParser::GetInstance()->GetMapLayers();
}
void Engine::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	MapParser::GetInstance()->Render();
	std::vector<GameObject*>::iterator it;
	for (it = staticObjectList.begin();it != staticObjectList.end();it++)
		(*it)->Render();

	for (it = movingObjectList.begin();it != movingObjectList.end();it++)
		(*it)->Render();
	player->Render();
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