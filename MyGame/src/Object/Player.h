#ifndef PLAYER_H
#define PLAYER_H
#include "MovingObject.h"
#include "SDL.h"
class Player:public MovingObject
{
public:
	Player(ObjectProperty objectProperty);
	virtual void Update(float dt);
	virtual bool CheckCollisionToObject(SDL_Rect objectCollider);
	virtual SDL_Rect GetCollider() { return movingObject->GetCollider(); }
	virtual void Render();
	virtual void Clean();
private:
	int isHitCD;
	MovingObject* movingObject;
};
#endif

