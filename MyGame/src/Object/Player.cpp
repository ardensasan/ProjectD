#include "Player.h"
#include "Input.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include "Camera.h"
const float MOVEX = 5.0f;
const float MOVEHIT = -10.0f;
const float JUMP = -12.0f;
Player::Player(ObjectProperty objProp) {
	objectProperty = objProp;
	direction = 3;
	animation = new Animation(objectProperty.width, objectProperty.height);
	boxCollider = new BoxCollider();
	yVelocity = 1;
	isHit = false;
	isHitCD = 200;
}

void Player::Update() {
	if (direction == 1)
		flip = SDL_FLIP_NONE;
	else if (direction == -1)
		flip = SDL_FLIP_HORIZONTAL;

	yVelocity++;
	animation->SetProperty(objectProperty.name+"_idle", flip);
	//move left
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && isHitCD > 50) {
		direction = -1;
		animation->SetProperty(objectProperty.name + "_run", flip);
		MoveXPosition(MOVEX * direction);
	}
	//move right
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) && isHitCD > 50) {
		direction = 1;
		animation->SetProperty(objectProperty.name + "_run", flip);
		MoveXPosition(MOVEX * direction);
	}
	//jump
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && isOnGround && isHitCD > 50) {
		yVelocity = JUMP;
	}
	if (yVelocity > 10)
		yVelocity = 10;
	if(yVelocity < 0)
		animation->SetProperty(objectProperty.name + "_jump", flip);
	if(yVelocity >= 0 && !isOnGround)
		animation->SetProperty(objectProperty.name + "_fall", flip);
	if (isHit) {
		animation->SetProperty(objectProperty.name + "_hit", flip);
		isHitCD++;
		if (isHitCD >= 150)
			isHit = false;
	}
	if (xVelocity > 0)
		xVelocity--;
	else if (xVelocity < 0)
		xVelocity+=2;
	MoveXPosition(xVelocity);
	MoveYPosition();
	animation->Update();
	Camera::GetInstance()->Update(objectProperty.xPosition, objectProperty.yPosition);
}

void Player::MoveXPosition(float x) {
	int OGX = objectProperty.xPosition;
	objectProperty.xPosition += x;
	boxCollider->Update(objectProperty);
	if (CollisionHandler::GetInstance()->CheckObjectMapCollision(boxCollider->GetBoxCollider(), 0)) {
		objectProperty.xPosition = OGX;
	}
}

void Player::MoveYPosition() {
	isOnGround = false;
	float y = yVelocity;
	int OGY = objectProperty.yPosition;
	objectProperty.yPosition += y;
	boxCollider->Update(objectProperty);
	if (y > 0) {
		if (CollisionHandler::GetInstance()->CheckObjectMapCollision(boxCollider->GetBoxCollider(), 4)) {
			objectProperty.yPosition = OGY;
			for (int i = 0; i < (int)y; i++)
			{
				objectProperty.yPosition++;
				boxCollider->Update(objectProperty);
				if (CollisionHandler::GetInstance()->CheckObjectMapCollision(boxCollider->GetBoxCollider(), 4)) {
					objectProperty.yPosition--;
					isOnGround = true;
				}
			}
		}
	}
	else if (y < 0) {
		if (CollisionHandler::GetInstance()->CheckObjectMapCollision(boxCollider->GetBoxCollider(), 2)) {
			objectProperty.yPosition = OGY;
			yVelocity = 0;
		}
	}
}
//check if player hits an enemy
void Player::CollisionToObject(SDL_Rect enemyBox) {
	if (CollisionHandler::GetInstance()->CheckCollisionToObject(boxCollider->GetBoxCollider(), enemyBox)) {
		isHit = true;
		isHitCD = 0;
		xVelocity = MOVEHIT*direction;
	}
}

void Player::Render() {
	animation->Render((int)objectProperty.xPosition, (int)objectProperty.yPosition);
}
void Player::Clean(){
	delete animation;
	delete boxCollider;
}