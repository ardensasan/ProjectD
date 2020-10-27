#include "GameObject.h"
GameObject::GameObject() {
	objectProperty = new ObjectProperty();
}
void GameObject::SetProperties(std::string id,int w, int h) {
	objectProperty->objProperty.textureID = id;
	objectProperty->objProperty.width = w;
	objectProperty->objProperty.height = h;
}