#include "Player.h"
#include "Input.h"
#include "Camera.h"
#include "CollisionHandler.h"
const float MOVEX = 4.0f;
const float MOVEHIT = -10.0f;
const float JUMP = -8.0f;
Player::Player(ObjectProperty objProp) {
	objectProperty = objProp;
	direction = 3;
	animation = new Animation(objectProperty.width, objectProperty.height);
	boxCollider = new BoxCollider();
	yVelocity = 1;
	isHit = false;
	isHitCD = 200;
}

void Player::Update(float dt) {
	if (direction == 1)
		flip = SDL_FLIP_NONE;
	else if (direction == -1)
		flip = SDL_FLIP_HORIZONTAL;

	yVelocity+=0.5f;
	animation->SetProperty(objectProperty.name+"_idle", flip);
	//move left
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && isHitCD > 50) {
		direction = -1;
		animation->SetProperty(objectProperty.name + "_run", flip);
		MoveXPosition(dt, MOVEX * direction);
	}
	//move right
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) && isHitCD > 50) {
		direction = 1;
		animation->SetProperty(objectProperty.name + "_run", flip);
		MoveXPosition(dt, MOVEX * direction);
	}
	//jump
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && isOnGround && isHitCD > 50) {
		yVelocity = JUMP;
	}
	if (yVelocity > 8) {
		yVelocity = 8;
	}
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
		xVelocity-=0.5f;
	else if (xVelocity < 0)
		xVelocity+=0.5f;
	MoveXPosition(dt, xVelocity * dt);
	MoveYPosition(dt);
	animation->Update();
}

void Player::MoveXPosition(float dt, int x) {
	if (x > 0) {
		for (int i = 0; i < x; i++)
		{
			objectProperty.xPosition += dt;
			boxCollider->Update(objectProperty);
			if (CollisionHandler::GetInstance()->CheckObjectMapCollision(boxCollider->GetBoxCollider(), 0)) {
				objectProperty.xPosition -= dt;
				break;
			}
		}
	}
	if (x < 0) {
		for (int i = x; i < 0; i++)
		{
			objectProperty.xPosition -= dt;
			boxCollider->Update(objectProperty);
			if (CollisionHandler::GetInstance()->CheckObjectMapCollision(boxCollider->GetBoxCollider(), 0)) {
				objectProperty.xPosition += dt;
				break;
			}
		}
	}
}

void Player::MoveYPosition(float dt) {
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
				objectProperty.yPosition +=  dt;
				break;
			}
		}
	}
}
//check if player hits an enemy
void Player::CollisionToObject(SDL_Rect enemyBox, float dt) {
	if (CollisionHandler::GetInstance()->CheckCollisionToObject(boxCollider->GetBoxCollider(), enemyBox)) {
		isHit = true;
		isHitCD = 0;
		xVelocity = MOVEHIT*direction;
	}
}

void Player::Render() {
	animation->Render((int)objectProperty.xPosition, (int)objectProperty.yPosition);
	boxCollider->Render();
}
void Player::Clean(){
	delete animation;
	delete boxCollider;
}