#include "MovingObject.h"
#include "CollisionHandler.h"
MovingObject::MovingObject() {}
MovingObject::MovingObject(std::string id, int w, int h) {
	objProperty.textureID = id;
	objProperty.width = w;
	objProperty.height = h;
	objProperty.xPosition = 100;
	objProperty.yPosition = 100;
	direction = 3;
	animationDelay = 50;
	animation = new Animation();
}

void MovingObject::UpdatePosX(float x) {
	float X = objProperty.xPosition;
	if (x > 0) {
		for (int i = 0; i <= x; i++)
		{
			objProperty.xPosition += i;
			if (CollisionHandler::GetInstance()->CheckMapCollision(objProperty)) {
				objProperty.xPosition = X;
				break;
			}
			X = objProperty.xPosition;
		}
	}
	if (x < 0) {
		for (int i = (int)x; i <= 0; i++)
		{
			objProperty.xPosition += i;
			if (CollisionHandler::GetInstance()->CheckMapCollision(objProperty)) {
				objProperty.xPosition = X;
				break;
			}
			X = objProperty.xPosition;
		}
	}
}
void MovingObject::UpdatePosY(float y) {
	float Y = objProperty.yPosition;
	if (y > 0) {
		for (int i = 0; i <= y; i++)
		{
			objProperty.yPosition += i;
			if (CollisionHandler::GetInstance()->CheckMapCollision(objProperty, i)) {
				objProperty.yPosition = Y;
				break;
			}
			Y = objProperty.yPosition;
		}
	}
	if (y < 0) {
		for (int i = (int)y; i < 0; i++)
		{
			objProperty.yPosition += i;
			if (CollisionHandler::GetInstance()->CheckMapCollision(objProperty, i)) {
				objProperty.yPosition = Y;
				break;
			}
			Y = objProperty.yPosition;
		}
	}
}
void MovingObject::SetTexture(std::string id) {
	animation->SetProperty(id, objProperty.width, objProperty.height, animationDelay, flip);
}

void MovingObject::Update() {
	animation->Update();
}
void MovingObject::Draw(){
	animation->Draw(objProperty.xPosition, objProperty.yPosition, objProperty.width, objProperty.height);
}
void MovingObject::Clean(){}