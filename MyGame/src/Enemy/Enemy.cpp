#include "Enemy.h"
#include "Input.h"
#include "Camera.h"
#include "CollisionHandler.h"
const float MOVEX = 5.0f;
const float JUMP = -8.0f;
Enemy::Enemy(ObjectProperty objProp) {
	objectProperty = objProp;
	direction = 3;
	animation = new Animation(objectProperty.width, objectProperty.height);
	boxCollider = new BoxCollider();
	yVelocity = 1;
}

void Enemy::Update(float dt) {
	boxCollider->Update(objectProperty);
	animation->SetProperty(objectProperty.name + "_idle", flip);
	animation->Update();
}

void Enemy::MoveXPosition(float dt) {
}

void Enemy::MoveYPosition(float dt) {
}


void Enemy::Render() {
	animation->Render((int)objectProperty.xPosition, (int)objectProperty.yPosition);
	boxCollider->Render();
}
void Enemy::Clean() {
	delete animation;
	delete boxCollider;
}