#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "IObject.h"
#include "SDL.h"
#include <iostream>
struct ObjectProperty {
	std::string name;
	std::string type;
	float xPosition;
	float yPosition;
	int width;
	int height;
};

class GameObject:public IObject
{
public:
	GameObject() {}
	virtual void Update(float dt) {}
	virtual void Render() {}
	virtual void Clean() {}
private:
};
#endif

