#include "Chicken.h"
#include "Camera.h"
#include "CollisionHandler.h"
const float JUMP = -8.0f;
Chicken::Chicken(ObjectProperty objProp) {
	objectProperty = objProp;
	direction = -1;
	animation = new Animation(objectProperty.width, objectProperty.height);
	boxCollider = new BoxCollider();
	yVelocity = 1;
	moveSpeed = -2.0f;
	isOnGround = true;
	set = false;
	boundarySet = false;
}

void Chicken::Update(float dt) {
	if (direction == 1)
		flip = SDL_FLIP_NONE;
	else
		flip = SDL_FLIP_HORIZONTAL;
	yVelocity++;
	if (yVelocity > 2)
		yVelocity = 2;
	animation->SetProperty(objectProperty.name + "_idle", flip);
	if (set) {
		while (!movementBoundary->IsBoundarySet())
			movementBoundary->UpdateBoundary();
		boundarySet = true;
	}
	MoveYPosition(dt);
	boxCollider->Update(objectProperty);
	animation->Update();
	return;
}

void Chicken::CheckPlayerInBoundary(SDL_Rect playerBox, float dt) {
	if (boundarySet) {
		SDL_Rect objectCollider = boxCollider->GetBoxCollider();
		if (CollisionHandler::GetInstance()->IsInBoundary(movementBoundary->GetBoxCollider(), playerBox)) { // check if player is in the boundary
			if (playerBox.x <= objectCollider.x) {
				direction = 1;
				MoveXPosition(dt, moveSpeed * direction * dt);
			}
			else if (playerBox.x >= objectCollider.x + objectCollider.w) {
				direction = -1;
				MoveXPosition(dt, moveSpeed * direction * dt);
			}
		}
	}
}

void Chicken::MoveXPosition(float dt, float x) {
	if (x > 0) {
		for (int i = 0; i < (int)x; i++)
		{
			objectProperty.xPosition += dt;
			boxCollider->Update(objectProperty);
			if (CollisionHandler::GetInstance()->IsInBoundary(movementBoundary->GetBoxCollider(), boxCollider->GetBoxCollider())) {
				if (direction == -1 && (movementBoundary->GetBoxCollider().w + movementBoundary->GetBoxCollider().x) < (boxCollider->GetBoxCollider().x + boxCollider->GetBoxCollider().w)) {
					objectProperty.xPosition -= dt;
					direction = -direction;
					break;
				}
			}
		}
	}
	if (x < 0) {
		for (int i = (int)x; i < 0; i++)
		{
			objectProperty.xPosition -= dt;
			boxCollider->Update(objectProperty);
			if (CollisionHandler::GetInstance()->IsInBoundary(movementBoundary->GetBoxCollider(), boxCollider->GetBoxCollider())) {
				if (direction == 1 && movementBoundary->GetBoxCollider().x > boxCollider->GetBoxCollider().x) {
					objectProperty.xPosition += dt;
					direction = -direction;
					break;
				}
			}
		}
	}
	animation->SetProperty(objectProperty.name + "_run", flip);
	boxCollider->Update(objectProperty);
	return;
}

void Chicken::MoveYPosition(float dt) {
	isOnGround = false;
	float y = yVelocity;
	if (y > 0) {
		for (int i = 0; i < (int)y; i++)
		{

			objectProperty.yPosition += dt;
			boxCollider->Update(objectProperty);
			if (CollisionHandler::GetInstance()->CheckObjectMapCollision(boxCollider->GetBoxCollider(), 4)) {
				objectProperty.yPosition -= dt;
				isOnGround = true;
				if (!set) {
					set = true;
					movementBoundary = new MovementBoundary(objectProperty);
				}
				break;
			}
		}
	}
	else if (y < 0) {
		for (int i = (int)y; i < 0; i++)
		{
			objectProperty.yPosition -= dt;
			boxCollider->Update(objectProperty);
			if (CollisionHandler::GetInstance()->CheckObjectMapCollision(boxCollider->GetBoxCollider(), 2)) {
				yVelocity = 0;
				objectProperty.yPosition += dt;
				break;
			}
		}
	}
	return;
}


void Chicken::Render() {
	animation->Render((int)objectProperty.xPosition, (int)objectProperty.yPosition);
	//if (set) {
	//	movementBoundary->Render();
	//}
	return;
}
void Chicken::Clean() {
	delete animation;
	delete boxCollider;
	return;
}