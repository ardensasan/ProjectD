#ifndef ANIMATION_H
#define ANIMATION_H
#include "SDL.h"
#include <string>
class Animation
{
public:
	Animation(int w, int h);
	void SetProperty(std::string id, SDL_RendererFlip f);
	void Update();
	void Render(int x, int y);
	void Clean();
private:
	std::string textureID;
	int width, height;
	int frameRow, frameCol, frameMaxRow, frameMaxCol, animationDelay;
	SDL_RendererFlip flip;

};
#endif

