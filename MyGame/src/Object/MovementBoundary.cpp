#include "MovementBoundary.h"
#include "CollisionHandler.h"
MovementBoundary::MovementBoundary() {
	isBoundarySet = false;
}
MovementBoundary::MovementBoundary(ObjectProperty objProp) {
	leftBox = objProp;
	rightBox = objProp;
	leftBoxCollider = new BoxCollider();
	rightBoxCollider = new BoxCollider();
	boundaryCollider = new BoxCollider();
	isBoundarySet = false;
	leftLimitReached = false;
	rightLimitReached = false;
}

void MovementBoundary::UpdateBoundary() {
	leftBoxCollider->Update(leftBox);
	rightBoxCollider->Update(rightBox);
	if (!CollisionHandler::GetInstance()->CheckObjectMapCollision(leftBoxCollider->GetBoxCollider(), 0) && !leftLimitReached) { // left side boundary
		leftBox.xPosition--;
		SDL_Rect tempRect = { leftBox.xPosition - 10,leftBox.yPosition,10,leftBox.height };
		for (int i = 0; i < 3; i++)
		{
			tempRect.y++;
			if (!CollisionHandler::GetInstance()->CheckObjectMapCollision(tempRect, 4)) {
				tempRect.y--;
				leftLimitReached = true;
				break;
			}
		}
	}
	else if(CollisionHandler::GetInstance()->CheckObjectMapCollision(leftBoxCollider->GetBoxCollider(), 0) ){
		leftLimitReached = true;
	}

	if (!CollisionHandler::GetInstance()->CheckObjectMapCollision(rightBoxCollider->GetBoxCollider(), 0) && !rightLimitReached) { //right side boundary
		rightBox.width++;
		SDL_Rect tempRect = { rightBox.xPosition + rightBox.width,rightBox.yPosition,9,rightBox.height };
		for (int i = 0; i < 3; i++)
		{
			tempRect.y++;
			if (!CollisionHandler::GetInstance()->CheckObjectMapCollision(tempRect, 4)) {
				tempRect.y--;
				rightLimitReached = true;
				break;
			}
		}
	}else if (CollisionHandler::GetInstance()->CheckObjectMapCollision(rightBoxCollider->GetBoxCollider(), 0)) {
		rightLimitReached = true;
	}

	if (leftLimitReached && rightLimitReached) {
		leftBox.width = (rightBox.width + rightBox.xPosition) - leftBox.xPosition;
		boundaryCollider->Update(leftBox);
		isBoundarySet = true;
	}
}
bool MovementBoundary::IsBoundarySet() {
	return isBoundarySet;
}
void MovementBoundary::Render() {
}