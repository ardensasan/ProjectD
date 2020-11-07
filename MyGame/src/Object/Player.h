#ifndef PLAYER_H
#define PLAYER_H
#include "MovingObject.h"
#include "BoxCollider.h"
#include "Animation.h"
class Player:public MovingObject
{
public:
	Player(ObjectProperty objectProperty);
	void Update();
	inline SDL_Rect GetCollider() { return boxCollider->GetBoxCollider(); }
	void CollisionToObject(SDL_Rect enemyBox);
	bool IsHit() { return isHit; }
	void MoveXPosition(float x);
	void MoveYPosition();
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

