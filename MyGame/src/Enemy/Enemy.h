#ifndef ENEMY_H
#define ENEMY_H
#include "MovingObject.h"
#include "BoxCollider.h"
#include "Animation.h"
class Enemy :public MovingObject
{
public:
	Enemy(ObjectProperty objectProperty);
	void Update();
	inline SDL_Rect GetCollider() { return boxCollider->GetBoxCollider(); }
	void CollisionToObject(SDL_Rect enemyBox) {}
	bool IsHit() { return isHit; }
	void Render();
	void Clean();
private:
	int direction;
	float yVelocity;
	bool isOnGround;
	bool changeDirection;
	void MoveXPosition(float x);
	void MoveYPosition();
	SDL_RendererFlip flip;
	Animation* animation;
	BoxCollider* boxCollider;
	BoxCollider* tempBoxCollider;
};
#endif

