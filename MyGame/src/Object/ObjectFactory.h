#ifndef  OBJECTFACTORY_H
#define OBJECTFACTORY_H
#include "Enemy.h"
#include "Player.h"
#include "StaticObject.h"
#include <map>
#include <functional>

template<typename className> StaticObject* createStaticObject(ObjectProperty objectProperty) { return new className(objectProperty); }
template<typename className> Enemy* createEnemyObject(ObjectProperty objectProperty) { return new className(objectProperty); }

class ObjectFactory
{
public:
	static ObjectFactory* GetInstance();
	void LoadObjectMap(); // assign id to class in map
	StaticObject* CreateStaticObject(ObjectProperty objectProperty);
	Enemy* CreateEnemyObject(ObjectProperty objectProperty);
private:
	ObjectFactory();
	static ObjectFactory* instance;
	std::map<std::string, StaticObject* (*)(ObjectProperty objectProperty)> staticObjectMap;
	std::map<std::string, Enemy* (*)(ObjectProperty objectProperty)> enemyObjectMap;
};

#endif // ! OBJECTFACTORY_H
