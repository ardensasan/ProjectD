#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "IObject.h"
#include "SDL.h"
#include <iostream>
class GameObject:public IObject
{
public:
	GameObject();
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Clean() = 0;
protected:
};
#endif

