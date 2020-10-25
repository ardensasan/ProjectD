#include "Player.h"
#include "Input.h"
const float MOVELEFT = -5.0f;
const float MOVERIGHT = 5.0f;
const float MOVEUP = -5.0f;
const float MOVEDOWN = 5.0f;
Player::Player(std::string id, int width, int height) {
	SetProperties(id, width, height);
	animation = new Animation();
	rigidbody = new RigidBody();
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
		rigidbody->MovePosX(MOVELEFT);
		animation->SetProperty("player_run", width, height, 50, flip);
	}
	//move right
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
		direction = 3;
		rigidbody->MovePosX(MOVERIGHT);
		animation->SetProperty("player_run", width, height, 50, flip);
	}
	//move up 
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)) {
		direction = 2;
		rigidbody->MovePosY(MOVEUP);
		animation->SetProperty("player_run", width, height, 50, flip);
	}
	//move down 
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)) {
		direction = 4;
		rigidbody->MovePosY(MOVEDOWN);
		animation->SetProperty("player_run", width, height, 50, flip);
	}
	animation->Update();
}
void Player::Draw() {
	animation->Draw(rigidbody->GetPositionX(), rigidbody->GetPositionY(), width,height);
}
void Player::Clean(){
}