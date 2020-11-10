#ifndef PLAYER_H
#define PLAYER_H
#include "MovingObject.h"
#include "BoxCollider.h"
#include "Animation.h"
class Player:public MovingObject
{
public:
	Player(ObjectProperty objectProperty);
	void Update(float dt);
	inline SDL_Rect GetCollider() { return boxCollider->GetBoxCollider(); }
	virtual void CheckPlayerInBoundary(SDL_Rect playerBox, float dt) {}
	void CollisionToObject(SDL_Rect enemyBox, float dt);
	bool IsHit() { return isHit; }
	void MoveXPosition(float dt, float x);
	void MoveYPosition(float dt);
	void Render();
	void Clean();
private:
	int direction;
	bool isOnGround;
	SDL_RendererFlip flip;
	Animation* animation;
	BoxCollider* boxCollider;
};
#endif

