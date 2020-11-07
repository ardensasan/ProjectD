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
	virtual void Update(float dt) = 0;
	virtual SDL_Rect GetCollider() = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;
protected:
	ObjectProperty objectProperty;
private:
};
#endif

