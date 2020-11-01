#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "IObject.h"
#include "SDL.h"
#include <iostream>
struct ObjectProperty {
	std::string textureID;
	float xPosition;
	float yPosition;
	int width;
	int height;
};

class GameObject:public IObject
{
public:
	GameObject() {}
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;
private:
};
#endif

