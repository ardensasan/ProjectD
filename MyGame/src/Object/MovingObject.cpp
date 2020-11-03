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
	boxCollider = new BoxCollider();
}

void MovingObject::UpdatePosX(float x) {
	float X = objectProperty.xPosition;
	if (x > 0) {
		direction = 3;
		for (int i = 1; i <= x; i++)
		{
			objectProperty.xPosition++;
			boxCollider->Update(objectProperty.xPosition, objectProperty.yPosition, objectProperty.width, objectProperty.height,objectProperty.type);
			if (CollisionHandler::GetInstance()->CheckObjectMapCollision(boxCollider->GetBoxCollider(),0)) {
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
			boxCollider->Update(objectProperty.xPosition, objectProperty.yPosition, objectProperty.width, objectProperty.height,objectProperty.type);
			if (CollisionHandler::GetInstance()->CheckObjectMapCollision(boxCollider->GetBoxCollider(),0)) {
				objectProperty.xPosition++;
				break;
			}
		}
	}
	boxCollider->Update(objectProperty.xPosition, objectProperty.yPosition, objectProperty.width, objectProperty.height,objectProperty.type);
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
			boxCollider->Update(objectProperty.xPosition, objectProperty.yPosition, objectProperty.width, objectProperty.height,objectProperty.type);
			if (CollisionHandler::GetInstance()->CheckObjectMapCollision(boxCollider->GetBoxCollider(), movementDirection)) {
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
			boxCollider->Update(objectProperty.xPosition, objectProperty.yPosition, objectProperty.width, objectProperty.height,objectProperty.type);
			if (CollisionHandler::GetInstance()->CheckObjectMapCollision(boxCollider->GetBoxCollider(), movementDirection)) {
				objectProperty.yPosition++;
				jumpCollide = true;
				break;
			}
		}
	}
	boxCollider->Update(objectProperty.xPosition, objectProperty.yPosition, objectProperty.width, objectProperty.height,objectProperty.type);
}
void MovingObject::SetTexture(std::string id) {
	if (direction == 3)
		flip = SDL_FLIP_NONE;
	else if (direction == 1)
		flip = SDL_FLIP_HORIZONTAL;
	else
		flip = SDL_FLIP_NONE;
	animation->SetProperty(id, objectProperty.width, objectProperty.height, animationDelay, flip);
}
void MovingObject::Update() {
	Camera::GetInstance()->Update(objectProperty.xPosition, objectProperty.yPosition);
	boxCollider->Update(objectProperty.xPosition, objectProperty.yPosition, objectProperty.width, objectProperty.height,objectProperty.type);
	animation->Update();
}
void MovingObject::Render(){
	animation->Render(int(objectProperty.xPosition), int(objectProperty.yPosition), objectProperty.width, objectProperty.height);
	boxCollider->Render();
}
void MovingObject::Clean(){
	delete animation;
}