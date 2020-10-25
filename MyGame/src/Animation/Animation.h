#ifndef ANIMATION_H
#define ANIMATION_H
#include "SDL.h"
#include <string>
class Animation
{
public:
	Animation();
	void SetProperty(std::string id, int width, int height, int animationspeed, SDL_RendererFlip f);
	void Update();
	void Draw(int x, int y, int width, int height);
	void Clean();
private:
	std::string textureID;
	int frameRow, frameCol, frameMaxRow, frameMaxCol, animationDelay;
	SDL_RendererFlip flip;

};
#endif

