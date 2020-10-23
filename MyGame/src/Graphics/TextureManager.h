#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "SDL_image.h"
#include <string>
#include <map>
class TextureManager
{
public:
	static TextureManager* GetInstance();
	void Load(std::string id, std::string filename);
	void Draw();
	void Clean();
private:
	TextureManager();
	static TextureManager* instance;
	SDL_Texture* texture;
	std::map<std::string, SDL_Texture*> assetMap;
};
#endif
