#ifndef RHINO_H
#define RHINO_H
#include "Enemy.h"
class Rhino:public Enemy
{
public:
	Rhino(ObjectProperty objectProperty);
	virtual void Update(float dt);
	virtual inline SDL_Rect GetCollider() { return boxCollider->GetBoxCollider(); }
	virtual void CollisionToObject(SDL_Rect playerBox, float dt) {}
	virtual void CheckPlayerInBoundary(SDL_Rect playerBox, float dt);
	virtual void Render();
	virtual void Clean();
	virtual bool IsBoundarySet() {
		if (set)
			return movementBoundary->IsBoundarySet();
		return false;
	}
private:
	bool set;
	int direction;
	float yVelocity;
	float xVelocity;
	bool isOnGround;
	void MoveXPosition(float dt, float x);
	void MoveYPosition(float dt);
	SDL_RendererFlip flip;
	Animation* animation;
	BoxCollider* boxCollider;
	MovementBoundary* movementBoundary;
	bool boundarySet;
	bool playerDetected;
	bool hitWall;
	int hitWallCD;
};
#endif

