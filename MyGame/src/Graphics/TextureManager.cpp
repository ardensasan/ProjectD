#include "TextureManager.h"
#include "Engine.h"
#include "SDL_image.h"
#include <iostream>
TextureManager* TextureManager::instance = nullptr;
TextureManager::TextureManager() {
	texture = nullptr;
}
TextureManager* TextureManager::GetInstance() {
	if (instance == nullptr)
		instance = new TextureManager();
	return instance;
}

void TextureManager::Load(std::string id, std::string filename) {
	texture = IMG_LoadTexture(Engine::GetInstance()->GetRenderer(), filename.c_str());
	if (texture == nullptr) {
		SDL_Log("Failed to load texture %s", SDL_GetError());
	}
	assetMap[id] = texture;
}

void TextureManager::Draw() {
	srcRect = { 0,0,32,32 };
	texture = assetMap["player_idle"];
	SDL_RenderCopy(Engine::GetInstance()->GetRenderer(),texture,NULL,NULL);
}


void TextureManager::DrawTile(std::string id,int row,int col,int width, int height, int srcX, int srcY) {
	srcRect = { srcY * width,srcX* height,width,height };
	dstRect = { row * width,col * height,width,height };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), assetMap[id], &srcRect, &dstRect, 0, 0, SDL_FLIP_NONE);
}


void TextureManager::Clean() {
	std::map<std::string, SDL_Texture*>::iterator it;
	for (it = assetMap.begin();it != assetMap.end();it++) {
		SDL_DestroyTexture(it->second);
	}
	assetMap.clear();
}