#ifndef PLAYER_H
#define PLAYER_H
#include "MovingObject.h"
#include "SDL.h"
class Player:public MovingObject
{
public:
	Player(std::string id, int width, int height);
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Clean();
private:
	MovingObject* movingObject;
};

#endif

