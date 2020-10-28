#include "Player.h"
#include "Input.h"
#include "Camera.h"
#include "CollisionHandler.h"
const float MOVELEFT = -2.0f;
const float MOVERIGHT = 2.0f;
const float MOVEUP = -2.0f;
const float MOVEDOWN = 2.0f;
Player::Player(std::string id, int width, int height) {
	movingObject = new MovingObject(id, width, height);
	direction = 3;
;}

void Player::Update() {
	if (direction == 3)
		flip = SDL_FLIP_NONE;
	else if(direction == 1)
		flip = SDL_FLIP_HORIZONTAL;
	else
		flip = SDL_FLIP_HORIZONTAL;
	movingObject->SetTexture("player_idle");
	//move left
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
		direction = 1;
		movingObject->UpdatePosX(MOVELEFT);
		movingObject->SetTexture("player_run");
	}
	//move right
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
		direction = 3;
		movingObject->UpdatePosX(MOVERIGHT);
		movingObject->SetTexture("player_run");
	}
	//move up 
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)) {
		direction = 2;
		movingObject->UpdatePosY(MOVEUP);
		movingObject->SetTexture("player_run");
	}
	//move down 
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)) {
		direction = 4;
		movingObject->UpdatePosY(MOVEDOWN);
		movingObject->SetTexture("player_run");
	}
	movingObject->Update();
	CollisionHandler::GetInstance()->CheckMapCollision(movingObject->GetProperties());
	Camera::GetInstance()->Update(movingObject->GetPositionX(), movingObject->GetPositionY());
}
void Player::Draw() {
	movingObject->Draw();
}
void Player::Clean(){
	delete movingObject;
}