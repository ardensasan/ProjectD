#ifndef  OBJECTFACTORY_H
#define OBJECTFACTORY_H
#include "Enemy.h"
#include "Player.h"
#include "StaticObject.h"
#include <map>
#include <functional>
template<typename className> MovingObject* createMovingObject(ObjectProperty objectProperty) { return new className(objectProperty); }
template<typename className> StaticObject* createStaticObject(ObjectProperty objectProperty) { return new className(objectProperty); }

class ObjectFactory
{
public:
	static ObjectFactory* GetInstance();
	void LoadObjectMap(); // assign id to class in map
	StaticObject* CreateStaticObject(ObjectProperty objProp);
	MovingObject* CreateMovingObject(ObjectProperty objectProperty);
private:
	ObjectFactory();
	static ObjectFactory* instance;
	ObjectProperty objectProperty;
	std::map<std::string, MovingObject* (*)(ObjectProperty objectProperty)> movingObjectMap;
	std::map<std::string, StaticObject* (*)(ObjectProperty objectProperty)> staticObjectMap;
};

#endif // ! OBJECTFACTORY_H
