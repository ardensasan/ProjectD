#include "Player.h"
#include "Input.h"
#include "Camera.h"
#include "CollisionHandler.h"
const float MOVELEFT = -2.0f;
const float MOVERIGHT = 2.0f;
const float MOVEUP = -2.0f;
const float MOVEDOWN = 2.0f;
Player::Player(std::string id, int width, int height) {
	SetProperties(id, width, height);
	animation = new Animation();
	direction = 3;
;}

void Player::Update() {
	SDL_RendererFlip flip;
	if (direction == 3)
		flip = SDL_FLIP_NONE;
	else if(direction == 1)
		flip = SDL_FLIP_HORIZONTAL;
	else
		flip = SDL_FLIP_HORIZONTAL;
	animation->SetProperty("player_idle", objectProperty->GetWidth(), objectProperty->GetHeight(), 50, flip);
	//move left
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
		direction = 1;
		objectProperty->UpdatePosX(MOVELEFT);
		animation->SetProperty("player_run", objectProperty->GetWidth(), objectProperty->GetHeight(), 50, flip);
	}
	//move right
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
		direction = 3;
		objectProperty->UpdatePosX(MOVERIGHT);
		animation->SetProperty("player_run", objectProperty->GetWidth(), objectProperty->GetHeight(), 50, flip);
	}
	//move up 
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)) {
		direction = 2;
		objectProperty->UpdatePosY(MOVEUP);
		animation->SetProperty("player_run", objectProperty->GetWidth(), objectProperty->GetHeight(), 50, flip);
	}
	//move down 
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)) {
		direction = 4;
		objectProperty->UpdatePosY(MOVEDOWN);
		animation->SetProperty("player_run", objectProperty->GetWidth(), objectProperty->GetHeight(), 50, flip);
	}
	animation->Update();
	CollisionHandler::GetInstance()->CheckMapCollision(objectProperty->objProperty);
	Camera::GetInstance()->Update(objectProperty->GetPositionX(), objectProperty->GetPositionY());
}
void Player::Draw() {
	animation->Draw(objectProperty->GetPositionX(), objectProperty->GetPositionY(), objectProperty->GetWidth(), objectProperty->GetHeight());
}
void Player::Clean(){
	delete animation;
	delete objectProperty;
}