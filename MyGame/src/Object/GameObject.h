#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "IObject.h"
#include "SDL.h"
#include <iostream>
class GameObject:public IObject
{
public:
	void SetProperties(std::string textureID, int width, int height);
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual void Clean() = 0;
protected:
	int width, height;
	std::string textureID;
	SDL_RendererFlip flip;
	int direction; // 1=left 2=up 3=right 4=down

};
#endif

