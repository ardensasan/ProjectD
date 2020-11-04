#ifndef IOBJECT_H
#define IOBJECT_H
#include "SDL.h"
class IObject {
public:
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;
	virtual bool CheckCollisionToObject(SDL_Rect playerCollider) = 0;
	virtual SDL_Rect GetCollider() = 0;
};
#endif;