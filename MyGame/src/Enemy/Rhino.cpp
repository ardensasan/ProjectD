#include "Rhino.h"
#include "Camera.h"
#include "CollisionHandler.h"
const float JUMP = -8.0f;
Rhino::Rhino(ObjectProperty objProp) {
	objectProperty = objProp;
	direction = -1;
	animation = new Animation(objectProperty.width, objectProperty.height);
	boxCollider = new BoxCollider();
	yVelocity = 1;
	xVelocity = 0;
	isOnGround = true;
	set = false;
	boundarySet = false;
	playerDetected = false;
	hitWall = false;
	hitWallCD = 0;
}

void Rhino::Update(float dt) {
	if (direction == -1)
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
	if (playerDetected) {
		std::cout << xVelocity << std::endl;
		if (direction == 1 && playerDetected)
			xVelocity+=0.5f;
		if (direction == -1 && playerDetected)
			xVelocity-= 0.5f;
		if (xVelocity > 10)
			xVelocity = 10;
		if (xVelocity < -10)
			xVelocity = -10;
		MoveXPosition(dt, xVelocity * dt);
	}
	if (hitWall) {
		if (xVelocity < 0) {
			xVelocity+= 0.5f;
		}
		if (xVelocity > 0) {
			xVelocity-=0.5f;
		}
		if (xVelocity == 0 && hitWallCD > 100){
			hitWall = false;
			hitWallCD = 0;
		}
		hitWallCD++;
		MoveXPosition(dt, xVelocity * dt);
		animation->SetProperty(objectProperty.name + "_idle", flip);
		if(xVelocity != 0)
			animation->SetProperty(objectProperty.name + "_hit_wall", flip);
	}
	MoveYPosition(dt);
	boxCollider->Update(objectProperty);
	animation->Update();
	return;
}

void Rhino::CheckPlayerInBoundary(SDL_Rect playerBox, float dt) {
	if (boundarySet && !playerDetected && !hitWall) {
		SDL_Rect objectCollider = boxCollider->GetBoxCollider();
		if (CollisionHandler::GetInstance()->IsInBoundary(movementBoundary->GetBoxCollider(), playerBox)) { // check if player is in the boundary
			if (playerBox.x <= objectCollider.x) {
				direction = -1;
				playerDetected = true;
			}
			else if (playerBox.x >= objectCollider.x + objectCollider.w) {
				direction = 1;
				playerDetected = true;
			}
		}
	}
}

void Rhino::MoveXPosition(float dt, float x) {
	if (x > 0) {
		for (int i = 0; i < (int)x; i++)
		{
			objectProperty.xPosition += dt;
			boxCollider->Update(objectProperty);
			if (CollisionHandler::GetInstance()->IsInBoundary(movementBoundary->GetBoxCollider(), boxCollider->GetBoxCollider())) {
				if (direction == 1 && (movementBoundary->GetBoxCollider().w + movementBoundary->GetBoxCollider().x) < (boxCollider->GetBoxCollider().x + boxCollider->GetBoxCollider().w)) {
					objectProperty.xPosition -= dt;
					playerDetected = false;
					xVelocity = 8 * -direction;
					yVelocity = -5;
					hitWall = true;
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
				if (direction == -1 && movementBoundary->GetBoxCollider().x > boxCollider->GetBoxCollider().x) {
					objectProperty.xPosition += dt;
					playerDetected = false;
					xVelocity = 8 * -direction;
					yVelocity = -5;
					hitWall = true;
					break;
				}
			}
		}
	}
	animation->SetProperty(objectProperty.name + "_run", flip);
	boxCollider->Update(objectProperty);
	return;
}

void Rhino::MoveYPosition(float dt) {
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


void Rhino::Render() {
	animation->Render((int)objectProperty.xPosition, (int)objectProperty.yPosition);
	//if (set) {
	//	movementBoundary->Render();
	//}
	return;
}
void Rhino::Clean() {
	delete animation;
	delete boxCollider;
	return;
}