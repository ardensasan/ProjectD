#ifndef OBJECTPROPERTY_H
#define OBJECTPROPERTY_H
#include <string>
#include "GameObject.h"
struct ObjProperty {
	std::string textureID;
	float xPosition;
	float yPosition;
	int width;
	int height;
};

class ObjectProperty:public GameObject
{
public:
	ObjectProperty();
protected:
	ObjProperty objProperty;
	SDL_RendererFlip flip;
};

#endif

