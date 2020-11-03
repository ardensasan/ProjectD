#include "StaticObject.h"
#include "Camera.h"
StaticObject::StaticObject() {
}
StaticObject::StaticObject(ObjectProperty objProp) {
	objectProperty = objProp;
	animationDelay = 50;
	animation = new Animation();
	boxCollider = new BoxCollider();
	boxCollider->Update(objectProperty.xPosition, objectProperty.yPosition, objectProperty.width, objectProperty.height,objectProperty.type);
}

void StaticObject::Update(float dt) {
	//if (SDL_HasIntersection(&player->GetBoxCollider(), &boxCollider->GetBoxCollider())) {
	//	std::cout << "Piste";
	//}
	animation->SetProperty(objectProperty.name, objectProperty.width, objectProperty.height, 50, SDL_FLIP_NONE);
	Camera::GetInstance()->Update(objectProperty.xPosition, objectProperty.yPosition);
	animation->Update();
}

void StaticObject::Render() {
	animation->Render(int(objectProperty.xPosition), int(objectProperty.yPosition), objectProperty.width, objectProperty.height);
	boxCollider->Render();
}

void StaticObject::Clean() {
	delete animation;
	delete boxCollider;
}