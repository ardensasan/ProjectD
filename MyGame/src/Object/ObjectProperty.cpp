#include "ObjectProperty.h"
#include "CollisionHandler.h"
ObjectProperty::ObjectProperty() {
	objProperty.xPosition = 100.0f;
	objProperty.yPosition = 100.0f;
}

void ObjectProperty::UpdatePosX(float x){
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
		for (int i = x; i <= 0; i++)
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
void ObjectProperty::UpdatePosY(float y) {
	float Y = objProperty.yPosition;
	if (y > 0) {
		for (int i = 0; i <= y; i++)
		{
			objProperty.yPosition += i;
			if (CollisionHandler::GetInstance()->CheckMapCollision(objProperty,i)) {
				objProperty.yPosition = Y;
				break;
			}
			Y = objProperty.yPosition;
		}
	}
	if (y < 0) {
		for (int i = y; i < 0; i++)
		{
			objProperty.yPosition += i;
			if (CollisionHandler::GetInstance()->CheckMapCollision(objProperty,i)) {
				objProperty.yPosition = Y;
				break;
			}
			Y = objProperty.yPosition;
		}
	}
}