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
	void MoveXPosition(float dt);
	void MoveYPosition(float dt);
	SDL_RendererFlip flip;
	Animation* animation;
	BoxCollider* boxCollider;
};
#endif

