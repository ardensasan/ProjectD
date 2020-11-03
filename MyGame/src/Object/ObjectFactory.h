#ifndef  OBJECTFACTORY_H
#define OBJECTFACTORY_H
#include "Player.h"
#include "StaticObject.h"
class ObjectFactory
{
public:
	static ObjectFactory* GetInstance();
	GameObject* CreateObject(ObjectProperty objectProperty);
private:
	ObjectFactory();
	static ObjectFactory* instance;
};

#endif // ! OBJECTFACTORY_H
