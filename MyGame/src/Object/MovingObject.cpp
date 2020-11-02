#include "MovingObject.h"
#include "CollisionHandler.h"
#include "Camera.h"
MovingObject::MovingObject() {
	isOnGround = false;
}
MovingObject::MovingObject(ObjectProperty objProp) {
	objectProperty = objProp;
	animationDelay = 50;
	jumpCollide = false;
	animation = new Animation();
	boxColiider = new BoxCollider();
}

void MovingObject::UpdatePosX(float x) {
	float X = objectProperty.xPosition;
	if (x > 0) {
		direction = 3;
		for (int i = 1; i <= x; i++)
		{
			objectProperty.xPosition++;
			boxColiider->Update(objectProperty.xPosition, objectProperty.yPosition, objectProperty.width, objectProperty.height);
			if (CollisionHandler::GetInstance()->CheckObjectMapCollision(boxColiider->GetBoxCollider(),0)) {
				objectProperty.xPosition--;
				break;
			}
		}
	}
	if (x < 0) {
		direction = 1;
		for (int i = (int)x; i < 0; i++)
		{
			objectProperty.xPosition--;
			boxColiider->Update(objectProperty.xPosition, objectProperty.yPosition, objectProperty.width, objectProperty.height);
			if (CollisionHandler::GetInstance()->CheckObjectMapCollision(boxColiider->GetBoxCollider(),0)) {
				objectProperty.xPosition++;
				break;
			}
		}
	}
	boxColiider->Update(objectProperty.xPosition, objectProperty.yPosition, objectProperty.width, objectProperty.height);
}
void MovingObject::UpdatePosY(float y) {
	jumpCollide = false;
	float Y = objectProperty.yPosition;
	int movementDirection = 0;
	if (y > 0) {
		isOnGround = false;
		movementDirection = 4;
		for (int i = 1; i <= y; i++)
		{
			objectProperty.yPosition ++;
			boxColiider->Update(objectProperty.xPosition, objectProperty.yPosition, objectProperty.width, objectProperty.height);
			if (CollisionHandler::GetInstance()->CheckObjectMapCollision(boxColiider->GetBoxCollider(), movementDirection)) {
				objectProperty.yPosition--;
				isOnGround = true;
				break;
			}
		}
	}
	else if (y < 0) {
		movementDirection = 2;
		isOnGround = false;
		for (int i = (int)y; i < 0; i++)
		{
			objectProperty.yPosition--;
			boxColiider->Update(objectProperty.xPosition, objectProperty.yPosition, objectProperty.width, objectProperty.height);
			if (CollisionHandler::GetInstance()->CheckObjectMapCollision(boxColiider->GetBoxCollider(), movementDirection)) {
				objectProperty.yPosition++;
				jumpCollide = true;
				break;
			}
		}
	}
	boxColiider->Update(objectProperty.xPosition, objectProperty.yPosition, objectProperty.width, objectProperty.height);
}
void MovingObject::SetTexture(std::string id) {
	if (direction == 3)
		flip = SDL_FLIP_NONE;
	else if (direction == 1)
		flip = SDL_FLIP_HORIZONTAL;
	else
		flip = SDL_FLIP_HORIZONTAL;
	animation->SetProperty(id, objectProperty.width, objectProperty.height, animationDelay, flip);
}
void MovingObject::Update() {

	Camera::GetInstance()->Update(objectProperty.xPosition, objectProperty.yPosition);
	boxColiider->Update(objectProperty.xPosition, objectProperty.yPosition, objectProperty.width, objectProperty.height);
	animation->Update();
}
void MovingObject::Render(){
	animation->Render(int(objectProperty.xPosition), int(objectProperty.yPosition), objectProperty.width, objectProperty.height);
	boxColiider->Render();
}
void MovingObject::Clean(){
	delete animation;
}