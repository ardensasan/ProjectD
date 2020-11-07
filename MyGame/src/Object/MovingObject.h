#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H
#include "GameObject.h"
class MovingObject:public GameObject
{
public:
	MovingObject() {}
	virtual void Update() = 0;
	virtual SDL_Rect GetCollider() = 0;
	virtual void CollisionToObject(SDL_Rect enemyBox) = 0;
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

