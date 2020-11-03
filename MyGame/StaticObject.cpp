#include "StaticObject.h"
#include "Camera.h"
StaticObject::StaticObject() {
}
StaticObject::StaticObject(ObjectProperty objProp) {
	objectProperty = objProp;
	animationDelay = 50;
	animation = new Animation();
	boxCollider = new BoxCollider();
}

void StaticObject::Update(float dt) {
	boxCollider->Update(objectProperty.xPosition, objectProperty.yPosition, objectProperty.width, objectProperty.height, objectProperty.type);
	animation->SetProperty(objectProperty.name, objectProperty.width, objectProperty.height, 50, SDL_FLIP_NONE);
	Camera::GetInstance()->Update(objectProperty.xPosition, objectProperty.yPosition);
	animation->Update();
}

bool StaticObject::CheckCollisionToPlayer(SDL_Rect playerCollider) {
	return SDL_HasIntersection(&playerCollider, &boxCollider->GetBoxCollider());
}
void StaticObject::Render() {
	animation->Render(int(objectProperty.xPosition), int(objectProperty.yPosition), objectProperty.width, objectProperty.height);
	boxCollider->Render();
}

void StaticObject::Clean() {
	delete animation;
	delete boxCollider;
}