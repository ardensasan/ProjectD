#include "MovingObject.h"
#include "CollisionHandler.h"
#include "Camera.h"
MovingObject::MovingObject() {
	isOnGround = false;
}
MovingObject::MovingObject(std::string id, int w, int h) {
	objectProperty.textureID = id;
	objectProperty.width = w;
	objectProperty.height = h;
	objectProperty.xPosition = 100;
	objectProperty.yPosition = 100;
	animationDelay = 50;
	jumpCollide = false;
	animation = new Animation();
}

void MovingObject::UpdatePosX(float x) {
	float X = objectProperty.xPosition;
	if (x > 0) {
		direction = 3;
		for (int i = 1; i <= x; i++)
		{
			objectProperty.xPosition += i;
			if (CollisionHandler::GetInstance()->CheckMapCollision(objectProperty)) {
				objectProperty.xPosition = X;
				break;
			}
			X = objectProperty.xPosition;
		}
	}
	if (x < 0) {
		direction = 1;
		for (int i = (int)x; i < 0; i++)
		{
			objectProperty.xPosition += i;
			if (CollisionHandler::GetInstance()->CheckMapCollision(objectProperty)) {
				objectProperty.xPosition = X;
				break;
			}
			X = objectProperty.xPosition;
		}
	}
}
void MovingObject::UpdatePosY(float y) {
	jumpCollide = false;
	float Y = objectProperty.yPosition;
	if (y > 0) {
		isOnGround = false;
		for (int i = 1; i <= y; i++)
		{
			objectProperty.yPosition += i;
			if (CollisionHandler::GetInstance()->CheckMapCollision(objectProperty, i)) {
				objectProperty.yPosition = Y;
				isOnGround = true;
				break;
			}
			Y = objectProperty.yPosition;
		}
	}
	else if (y < 0) {
		isOnGround = false;
		for (int i = (int)y; i < 0; i++)
		{
			objectProperty.yPosition += i;
			if (CollisionHandler::GetInstance()->CheckMapCollision(objectProperty, i)) {
				objectProperty.yPosition = Y;
				jumpCollide = true;
				break;
			}
			Y = objectProperty.yPosition;
		}
	}
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
	animation->Update();
}
void MovingObject::Draw(){
	animation->Draw(objectProperty.xPosition, objectProperty.yPosition, objectProperty.width, objectProperty.height);
}
void MovingObject::Clean(){
	delete animation;
}