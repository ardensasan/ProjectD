#ifndef ENEMY_H
#define ENEMY_H
#include "MovingObject.h"
#include "BoxCollider.h"
#include "Animation.h"
class Enemy :public MovingObject
{
public:
	Enemy(ObjectProperty objectProperty);
	void Update(float dt);
	inline SDL_Rect GetCollider() { return boxCollider->GetBoxCollider(); }
	void CollisionToObject(SDL_Rect enemyBox, float dt) {}
	bool IsHit() { return isHit; }
	void Render();
	void Clean();
private:
	int direction;
	float yVelocity;
	bool isOnGround;
	bool changeDirection;
	void MoveXPosition(float dt, float x);
	void MoveYPosition(float dt);
	SDL_RendererFlip flip;
	Animation* animation;
	BoxCollider* boxCollider;
	BoxCollider* tempBoxCollider;
};
#endif

