#ifndef ENEMY_H
#define ENEMY_H
#include "GameObject.h"
#include "BoxCollider.h"
#include "Animation.h"
#include "MovementBoundary.h"
class Enemy :public GameObject
{
public:
	Enemy() {}
	virtual void Update(float dt) = 0;
	virtual inline SDL_Rect GetCollider() = 0;
	virtual void CollisionToObject(SDL_Rect enemyBox, float dt) = 0;
	virtual void CheckPlayerInBoundary(SDL_Rect playerBox, float dt) = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;
protected:
	float moveSpeed;
};
#endif

