#include "TextureManager.h"
#include "Engine.h"
#include "SDL_image.h"
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
	SDL_DestroyTexture(texture);
	texture = nullptr;
}
void TextureManager::Draw() {
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), NULL, NULL, NULL, 0, 0, SDL_FLIP_NONE);
}
void TextureManager::Clean() {
	std::map<std::string, SDL_Texture*>::iterator it;
	for (it = assetMap.begin();it != assetMap.end();it++) {
		SDL_DestroyTexture(it->second);
	}
	assetMap.clear();
}