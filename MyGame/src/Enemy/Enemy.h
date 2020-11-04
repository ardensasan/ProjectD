#ifndef ENEMY_H
#define ENEMY_H
#include "MovingObject.h"
#include "SDL.h"
class Enemy:public MovingObject
{
public:
	Enemy(ObjectProperty objectProperty);
	virtual void Update(float dt);
	virtual SDL_Rect GetCollider() { return movingObject->GetCollider(); }
	virtual void Render();
	virtual void Clean();
private:
	std::string enemyID;
	MovingObject* movingObject;
};
#endif

