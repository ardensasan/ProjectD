#include "Player.h"
#include "Input.h"
#include "Camera.h"

const float MOVELEFT = -5.0f;
const float MOVERIGHT = 5.0f;
const float JUMP = -8.0f;
Player::Player(ObjectProperty objectProperty) {
	movingObject = new MovingObject(objectProperty);
	gravity = 1;
	yVelocity = 5.0f;
	xVelocity = 0;
	isHitCD = 0;
	direction = 1;
}

void Player::Update(float dt) {
	if (yVelocity < 0) {
		yVelocity += 0.5f;
	}
	else {
		yVelocity++;
	}
	movingObject->SetTexture("player_idle");
	//move left
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && xVelocity == 0) {
		direction = 1;
		movingObject->UpdatePosX(MOVELEFT * dt);
		movingObject->SetTexture("player_run");
	}
	//move right
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) && xVelocity == 0) {
		direction = 3;
		movingObject->UpdatePosX(MOVERIGHT * dt);
		movingObject->SetTexture("player_run");
	}
	//space 
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && movingObject->IsOnGround()) {
		movingObject->SetTexture("player_run");
		yVelocity = JUMP;
	}
	if (movingObject->JumpCollide())
		yVelocity = 0;
	if (yVelocity > 8)
		yVelocity = 8;

	if (xVelocity > 0)
		xVelocity--;
	if (xVelocity < 0)
		xVelocity++;
	if (yVelocity > 0 && !movingObject->IsOnGround())
		movingObject->SetTexture("player_fall");
	if (yVelocity < 0 && !movingObject->IsOnGround())
		movingObject->SetTexture("player_jump");


	movingObject->UpdatePosX(xVelocity * dt);
	movingObject->UpdatePosY(yVelocity * dt);
	movingObject->Update();
}

bool Player::CheckCollisionToObject(SDL_Rect objectCollider) {
	if (SDL_HasIntersection(&movingObject->GetCollider(), &objectCollider) && !movingObject->IsHit()) {
		if (direction == 1)
			xVelocity = 12.0f;
		if (direction == 3)
			xVelocity = -12.0f;
		movingObject->SetIsHit(true);
	}
	return true;
}

void Player::Render() {
	movingObject->Render();
}
void Player::Clean(){
	delete movingObject;
}