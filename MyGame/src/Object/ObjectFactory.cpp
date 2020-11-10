#include "ObjectFactory.h"
#include "Chicken.h"
#include "Rhino.h"
ObjectFactory* ObjectFactory::instance = nullptr;
ObjectFactory::ObjectFactory(){}
ObjectFactory* ObjectFactory::GetInstance() {
	if (instance == nullptr)
		instance = new ObjectFactory();
	return instance;
}


void ObjectFactory::LoadObjectMap() {
	staticObjectMap["Fruit"] = &createStaticObject<StaticObject>;
	enemyObjectMap["Chicken"] = &createEnemyObject<Chicken>;
	enemyObjectMap["Rhino"] = &createEnemyObject<Rhino>;
}

StaticObject* ObjectFactory::CreateStaticObject(ObjectProperty objectProperty) {
	std::map<std::string, StaticObject* (*)(ObjectProperty objectProperty)>::iterator it;
	for (it = staticObjectMap.begin();it != staticObjectMap.end();it++) {
		if(objectProperty.type == it->first)
		return it->second(objectProperty);
	}
}


Enemy* ObjectFactory::CreateEnemyObject(ObjectProperty objectProperty) {
	std::map<std::string, Enemy* (*)(ObjectProperty objectProperty)>::iterator it;
	for (it = enemyObjectMap.begin();it != enemyObjectMap.end();it++) {
		if (objectProperty.name == it->first)
			return it->second(objectProperty);
	}
}
