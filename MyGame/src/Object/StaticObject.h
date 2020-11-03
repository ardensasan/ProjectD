#ifndef STATICOBJECT_H
#define STATICOBJECT_H
#include "GameObject.h"
#include "Animation.h"
#include "BoxCollider.h"
#include "Player.h"
class StaticObject:public GameObject
{
public:
	StaticObject();
	StaticObject(ObjectProperty objProp);
	virtual void Update(float dt);
	virtual void Render();
	virtual void Clean();
	SDL_Rect GetBoxCollider() { return boxCollider->GetBoxCollider(); }
private:
	Animation* animation;
	BoxCollider* boxCollider;
	int animationDelay;
	ObjectProperty objectProperty;
};
#endif

