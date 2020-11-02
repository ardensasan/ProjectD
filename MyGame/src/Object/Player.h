#ifndef PLAYER_H
#define PLAYER_H
#include "MovingObject.h"
#include "SDL.h"
class Player:public MovingObject
{
public:
	Player(ObjectProperty objectProperty);
	virtual void Update(float dt);
	virtual void Render();
	virtual void Clean();
private:
	MovingObject* movingObject;
};
#endif

