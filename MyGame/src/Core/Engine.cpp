#include "Engine.h"
#include "TextureManager.h"
#include "MapParser.h"
#include "Input.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include "ObjectFactory.h"
#include "Timer.h"
Engine* Engine::instance = nullptr;
Engine::Engine() {
	bIsRunning = false;
	window = nullptr;
	renderer = renderer;
	boundariesSet = false;
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
				TextureManager::GetInstance()->Load("VirtualGuy_idle","assets/Player/Idle.png");
				TextureManager::GetInstance()->Load("VirtualGuy_fall", "assets/Player/Fall.png");
				TextureManager::GetInstance()->Load("VirtualGuy_jump", "assets/Player/Jump.png");
				TextureManager::GetInstance()->Load("VirtualGuy_run", "assets/Player/Run.png");
				TextureManager::GetInstance()->Load("VirtualGuy_hit", "assets/Player/Hit.png");
				//load fruit assets
				TextureManager::GetInstance()->Load("Apple", "assets/Items/Fruits/Apple.png");
				TextureManager::GetInstance()->Load("Banana", "assets/Items/Fruits/Banana.png");
				TextureManager::GetInstance()->Load("Cherry", "assets/Items/Fruits/Cherry.png");
				TextureManager::GetInstance()->Load("Kiwi", "assets/Items/Fruits/Kiwi.png");
				TextureManager::GetInstance()->Load("Melon", "assets/Items/Fruits/Melon.png");
				//load enemy assets
				TextureManager::GetInstance()->Load("AngryPig_idle", "assets/Enemies/AngryPig/Idle (36x30).png");
				TextureManager::GetInstance()->Load("AngryPig_run", "assets/Enemies/AngryPig/Run (36x30).png");
				TextureManager::GetInstance()->Load("Chicken_idle", "assets/Enemies/Chicken/Idle (32x34).png");
				TextureManager::GetInstance()->Load("Chicken_run", "assets/Enemies/Chicken/Run (32x34).png");
				TextureManager::GetInstance()->Load("Bunny_idle", "assets/Enemies/Bunny/Idle (34x44).png");
				TextureManager::GetInstance()->Load("Rhino_idle", "assets/Enemies/Rhino/Idle (52x34).png");
				TextureManager::GetInstance()->Load("Rhino_run", "assets/Enemies/Rhino/Run (52x34).png");
				TextureManager::GetInstance()->Load("Rhino_hit_wall", "assets/Enemies/Rhino/Hit Wall (52x34).png");
				TextureManager::GetInstance()->Load("Mushroom_idle", "assets/Enemies/Mushroom/Idle (32x32).png");
				TextureManager::GetInstance()->Load("Mushroom_run", "assets/Enemies/Mushroom/Run (32x32).png");
				Camera::GetInstance()->Set(screenWidth, screenHeight);
				if (!MapParser::GetInstance()->Load()) {
					bIsRunning = false;
					MapParser::GetInstance()->Clean();
				}
				else {
					ObjectFactory::GetInstance()->LoadObjectMap();
					staticObjectList.clear();
					movingObjectList.clear();
					std::vector<ObjectProperty> objectPropertyList;
					objectPropertyList = MapParser::GetInstance()->GetStaticObjects();
					std::vector<ObjectProperty>::iterator it;
					for (it = objectPropertyList.begin();it != objectPropertyList.end();it++)
						staticObjectList.push_back(ObjectFactory::GetInstance()->CreateStaticObject(*it));
					objectPropertyList.clear();
					objectPropertyList = MapParser::GetInstance()->GetMovingObjects();
					for (it = objectPropertyList.begin();it != objectPropertyList.end();it++) {
						if (it->type == "Player")
							player = new Player(*it);
						else if(it->type == "Enemy")
							enemyObjectList.push_back(ObjectFactory::GetInstance()->CreateEnemyObject(*it));
					}
					objectPropertyList.clear();
					bIsRunning = true;
				}
				
			}
		}
	}
	return;
}
void Engine::Events() {
	Input::GetInstance()->Listen();
}

void Engine::Update() {
	float dt = Timer::GetInstance()->GetDeltaTime();
	std::vector<GameObject*>::iterator it;
	player->Update(dt);
	for (it = staticObjectList.begin();it != staticObjectList.end();it++) {
		(*it)->Update(dt);
		if (CollisionHandler::GetInstance()->CheckCollisionToObject(player->GetCollider(), (*it)->GetCollider())) {
			it = staticObjectList.erase(it);
			if (it >= staticObjectList.end())
				break;
		}
	}
	std::vector<Enemy*>::iterator it2;
	for (it2 = enemyObjectList.begin();it2 != enemyObjectList.end();it2++) {
		(*it2)->Update(dt);
		if((*it2)->IsBoundarySet())
			(*it2)->CheckPlayerInBoundary(player->GetCollider(),dt);
		if(!player->IsHit())
			player->CollisionToObject((*it2)->GetCollider(),dt);
	}
	MapParser::GetInstance()->GetMapLayers();
	return;
}
void Engine::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	MapParser::GetInstance()->Render();
	std::vector<GameObject*>::iterator it;
	for (it = staticObjectList.begin();it != staticObjectList.end();it++)
		(*it)->Render();

	std::vector<Enemy*>::iterator it2;
	for (it2 = enemyObjectList.begin();it2 != enemyObjectList.end();it2++)
		(*it2)->Render();
	player->Render();
	SDL_RenderPresent(renderer);
	return;
}
void Engine::Clean() {
	TextureManager::GetInstance()->Clean();
	MapParser::GetInstance()->Clean();
	CollisionHandler::GetInstance()->Clean();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = nullptr;
	renderer = nullptr;
	return;
}

void Engine::Quit() {
	bIsRunning = false;
	return;
}