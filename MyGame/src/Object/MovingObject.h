#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H
#include "GameObject.h"
class MovingObject:public GameObject
{
public:
	MovingObject() {}
	virtual void Update(float dt) = 0;
	virtual SDL_Rect GetCollider() = 0;
	virtual void CollisionToObject(SDL_Rect enemyBox, float dt) = 0;
	virtual void CheckPlayerInBoundary(SDL_Rect playerBox, float dt) = 0;
	virtual bool IsHit() = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;
protected:
	bool isHit;
	int isHitCD; //cool down before object can be hit again
	float xVelocity,yVelocity;
	ObjectProperty objectProperty;
};
#endif

