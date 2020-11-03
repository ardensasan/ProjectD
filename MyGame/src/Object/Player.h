#ifndef PLAYER_H
#define PLAYER_H
#include "MovingObject.h"
#include "SDL.h"
class Player:public MovingObject
{
public:
	Player(ObjectProperty objectProperty);
	void UpdatePosX(float x);
	void UpdatePosY(float y);
	virtual void Update(float dt);
	virtual SDL_Rect GetCollider() { return movingObject->GetCollider(); }
	virtual void Render();
	virtual void Clean();
private:
	MovingObject* movingObject;
};
#endif

