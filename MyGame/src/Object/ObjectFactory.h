#ifndef  OBJECTFACTORY_H
#define OBJECTFACTORY_H
#include "Player.h"
class ObjectFactory
{
public:
	static ObjectFactory* GetInstance();
	GameObject* CreateObject(std::string className, ObjectProperty objectProperty);
private:
	ObjectFactory();
	static ObjectFactory* instance;
};

#endif // ! OBJECTFACTORY_H
