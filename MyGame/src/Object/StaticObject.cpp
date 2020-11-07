#include "StaticObject.h"
#include "Camera.h"
StaticObject::StaticObject(ObjectProperty objProp) {
	objectProperty = objProp;
	animationDelay = 50;
	animation = new Animation(objectProperty.width, objectProperty.height);
	boxCollider = new BoxCollider();
}

void StaticObject::Update() {
	boxCollider->Update(objectProperty);
	animation->SetProperty(objectProperty.name, SDL_FLIP_NONE);
	animation->Update();
}

void StaticObject::Render() {
	animation->Render(int(objectProperty.xPosition), int(objectProperty.yPosition));
	boxCollider->Render();
}

void StaticObject::Clean() {
	delete animation;
	delete boxCollider;
}