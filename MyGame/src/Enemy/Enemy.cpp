#include "Enemy.h"
#include "Input.h"
#include "Camera.h"
#include "CollisionHandler.h"
const float MOVEX = -2.0f;
const float JUMP = -8.0f;
Enemy::Enemy(ObjectProperty objProp) {
	objectProperty = objProp;
	direction = -1;
	animation = new Animation(objectProperty.width, objectProperty.height);
	boxCollider = new BoxCollider();
	tempBoxCollider = new BoxCollider();
	yVelocity = 1;
	xVelocity = 0;
	isOnGround = true;
	changeDirection = false;
}

void Enemy::Update() {
	yVelocity++;
	if (yVelocity > 2)
		yVelocity = 2;
	animation->SetProperty(objectProperty.name + "_idle", flip);
	MoveXPosition(MOVEX*direction);
	if (changeDirection)
		direction = -direction;
	if (direction == 1)
		flip = SDL_FLIP_NONE;
	else
		flip = SDL_FLIP_HORIZONTAL;
	MoveYPosition();
	boxCollider->Update(objectProperty);
	animation->Update();

	ObjectProperty tempObjectProperty = objectProperty;
	tempObjectProperty.xPosition -= tempObjectProperty.width * direction;
	tempBoxCollider->Update(tempObjectProperty);
	return;
}

void Enemy::MoveXPosition(float x) {
	if (x > 0) {
		for (int i = 0; i < (int)x; i++)
		{
			objectProperty.xPosition ++;
			boxCollider->Update(objectProperty);
			if (CollisionHandler::GetInstance()->CheckObjectMapCollision(boxCollider->GetBoxCollider(), 0)) {
				objectProperty.xPosition --;
				changeDirection = true;
				break;
			}
		}
	}
	if (x < 0) {
		for (int i = (int)x; i < 0; i++)
		{
			objectProperty.xPosition --;
			boxCollider->Update(objectProperty);
			if (CollisionHandler::GetInstance()->CheckObjectMapCollision(boxCollider->GetBoxCollider(), 0)) {
				objectProperty.xPosition ++;
				changeDirection = true;
				break;
			}
		}
	}
	animation->SetProperty(objectProperty.name + "_run", flip);
	return;
}

void Enemy::MoveYPosition() {
	changeDirection = true;
	isOnGround = false;
	float y = yVelocity;
	if (y > 0) {
		for (int i = 0; i < (int)y; i++)
		{

			objectProperty.yPosition ++;
			boxCollider->Update(objectProperty);

			ObjectProperty tempObjectProperty = objectProperty;
			tempObjectProperty.xPosition -= tempObjectProperty.width* direction;
			tempBoxCollider->Update(tempObjectProperty);
			tempObjectProperty.yPosition ++;
			tempBoxCollider->Update(tempObjectProperty);
			if (CollisionHandler::GetInstance()->CheckObjectMapCollision(tempBoxCollider->GetBoxCollider(), 4)) {
				changeDirection = false;
			}
			if (CollisionHandler::GetInstance()->CheckObjectMapCollision(boxCollider->GetBoxCollider(), 4)) {
				objectProperty.yPosition --;
				isOnGround = true;
				break;
			}
		}
	}
	else if (y < 0) {
		for (int i = (int)y; i < 0; i++)
		{
			objectProperty.yPosition --;
			boxCollider->Update(objectProperty);
			if (CollisionHandler::GetInstance()->CheckObjectMapCollision(boxCollider->GetBoxCollider(), 2)) {
				yVelocity = 0;
				objectProperty.yPosition ++;
				break;
			}
		}
	}
	return;
}


void Enemy::Render() {
	animation->Render((int)objectProperty.xPosition, (int)objectProperty.yPosition);
	return;
}
void Enemy::Clean() {
	delete animation;
	delete boxCollider;
	return;
}