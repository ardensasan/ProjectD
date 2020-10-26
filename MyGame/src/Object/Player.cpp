#include "Player.h"
#include "Input.h"
#include "Camera.h"
const float MOVELEFT = -5.0f;
const float MOVERIGHT = 5.0f;
const float MOVEUP = -5.0f;
const float MOVEDOWN = 5.0f;
Player::Player(std::string id, int width, int height) {
	SetProperties(id, width, height);
	animation = new Animation();
	position = new Position();
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
	animation->SetProperty("player_idle", width, height, 50, flip);
	//move left
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
		direction = 1;
		position->UpdatePosX(MOVELEFT);
		animation->SetProperty("player_run", width, height, 50, flip);
	}
	//move right
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
		direction = 3;
		position->UpdatePosX(MOVERIGHT);
		animation->SetProperty("player_run", width, height, 50, flip);
	}
	//move up 
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)) {
		direction = 2;
		position->UpdatePosY(MOVEUP);
		animation->SetProperty("player_run", width, height, 50, flip);
	}
	//move down 
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)) {
		direction = 4;
		position->UpdatePosY(MOVEDOWN);
		animation->SetProperty("player_run", width, height, 50, flip);
	}
	animation->Update();
	Camera::GetInstance()->Update(position->GetPositionX(), position->GetPositionY());
}
void Player::Draw() {
	animation->Draw(position->GetPositionX(), position->GetPositionY(), width,height);
}
void Player::Clean(){
}