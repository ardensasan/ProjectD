#include "ObjectFactory.h"
ObjectFactory* ObjectFactory::instance = nullptr;
ObjectFactory::ObjectFactory(){}
ObjectFactory* ObjectFactory::GetInstance() {
	if (instance == nullptr)
		instance = new ObjectFactory();
	return instance;
}
GameObject* ObjectFactory::CreateObject(ObjectProperty objectProperty) {
	if(objectProperty.type == "Fruit")
		return new StaticObject(objectProperty);
	if (objectProperty.type == "Player")
		return new Player(objectProperty);
}