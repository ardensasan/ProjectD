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
	virtual bool CheckCollisionToObject(SDL_Rect objectCollider);
	virtual void Render();
	virtual void Clean();
	virtual SDL_Rect GetCollider() { return boxCollider->GetBoxCollider(); }
private:
	Animation* animation;
	BoxCollider* boxCollider;
	int animationDelay;
	ObjectProperty objectProperty;
};
#endif

