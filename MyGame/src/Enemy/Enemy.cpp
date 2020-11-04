#include "Enemy.h"
#include "Camera.h"

const float MOVELEFT = -5.0f;
const float MOVERIGHT = 5.0f;
Enemy::Enemy(ObjectProperty objectProperty) {
	movingObject = new MovingObject(objectProperty);
	gravity = 1;
	yVelocity = 5.0f;
	xVelocity = 0;
	enemyID = objectProperty.name;
}

void Enemy::Update(float dt) {
	if (yVelocity < 0) {
		yVelocity += 0.5f;
	}
	else {
		yVelocity++;
	}
	movingObject->SetTexture(enemyID +"_idle");
	//move left
	if (movingObject->JumpCollide())
		yVelocity = 0;
	if (yVelocity > 8)
		yVelocity = 8;
	movingObject->UpdatePosY(yVelocity * dt);
	movingObject->Update();
}

void Enemy::Render() {
	movingObject->Render();
}
void Enemy::Clean() {
	delete movingObject;
}