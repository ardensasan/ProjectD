#ifndef STATICOBJECT_H
#define STATICOBJECT_H
#include "GameObject.h"
#include "Animation.h"
#include "BoxCollider.h"
class StaticObject:public GameObject
{
public:
	StaticObject(ObjectProperty objProp);
	void Update(float dt);
	inline SDL_Rect GetCollider() { return boxCollider->GetBoxCollider(); }
	void Follow(ObjectProperty objectProperty);
	void Render();
	void Clean();
private:
	Animation* animation;
	BoxCollider* boxCollider;
	int animationDelay;
};
#endif

