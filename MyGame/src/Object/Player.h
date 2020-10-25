#ifndef PLAYER_H
#define PLAYER_H
#include "GameObject.h"
#include "Animation.h"
#include "RigidBody.h"
#include "SDL.h"
class Player:public GameObject
{
public:
	Player(std::string id, int width, int height);
	virtual void Update();
	virtual void Draw();
	virtual void Clean();
private:
	Animation* animation;
	RigidBody* rigidbody;
};

#endif

