#include "Player.h"
#include "Input.h"
#include "Camera.h"

const float MOVELEFT = -3.0f;
const float MOVERIGHT = 3.0f;
Player::Player(std::string id, int width, int height) {
	movingObject = new MovingObject(id, width, height);
	direction = 3;
	gravity = 1;
	yVelocity = 5.0f;
	xVelocity = 0;
;}

void Player::Update(float dt) {
	if (yVelocity < 0) {
		yVelocity += 0.5f;
	}
	else {
		yVelocity++;
	}
	movingObject->SetTexture("player_idle");
	//move left
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
		direction = 1;
		movingObject->UpdatePosX(MOVELEFT*dt);
		movingObject->SetTexture("player_run");
	}
	//move right
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
		direction = 3;
		movingObject->UpdatePosX(MOVERIGHT*dt);
		movingObject->SetTexture("player_run");
	}
	//space 
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && movingObject->IsOnGround()) {
		direction = 4;
		movingObject->SetTexture("player_run");
		yVelocity = -6.0f;
	}
	if (movingObject->JumpCollide())
		yVelocity = 0;
	if (yVelocity > 4)
		yVelocity = 4;
	if (yVelocity > 0 && !movingObject->IsOnGround())
		movingObject->SetTexture("player_fall");
	if ( yVelocity < 0 && !movingObject->IsOnGround())
		movingObject->SetTexture("player_jump");
	movingObject->UpdatePosY(yVelocity * dt);
	movingObject->Update();
}

void Player::Draw() {
	movingObject->Draw();
}
void Player::Clean(){
	delete movingObject;
}