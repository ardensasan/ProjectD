#include "ObjectFactory.h"
ObjectFactory* ObjectFactory::instance = nullptr;
ObjectFactory::ObjectFactory(){}
ObjectFactory* ObjectFactory::GetInstance() {
	if (instance == nullptr)
		instance = new ObjectFactory();
	return instance;
}


void ObjectFactory::LoadObjectMap() {
	movingObjectMap["Player"] = &createMovingObject<Player>;
	staticObjectMap["Fruit"] = &createStaticObject<StaticObject>;
	movingObjectMap["Enemy"] = &createMovingObject<Enemy>;
}

StaticObject* ObjectFactory::CreateStaticObject(ObjectProperty objectProperty) {
	std::map<std::string, StaticObject* (*)(ObjectProperty objectProperty)>::iterator it;
	for (it = staticObjectMap.begin();it != staticObjectMap.end();it++) {
		if(objectProperty.type == it->first)
		return it->second(objectProperty);
	}
}

MovingObject* ObjectFactory::CreateMovingObject(ObjectProperty objectProperty) {
	std::map<std::string, MovingObject* (*)(ObjectProperty objectProperty)>::iterator it;
	for (it = movingObjectMap.begin();it != movingObjectMap.end();it++) {
		if (objectProperty.type == it->first)
			return it->second(objectProperty);
	}
}
