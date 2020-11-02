#include "ObjectFactory.h"
ObjectFactory* ObjectFactory::instance = nullptr;
ObjectFactory::ObjectFactory(){}
ObjectFactory* ObjectFactory::GetInstance() {
	if (instance == nullptr)
		instance = new ObjectFactory();
	return instance;
}

GameObject* ObjectFactory::CreateObject(std::string className, ObjectProperty objectProperty) {
	return new Player(objectProperty);
}