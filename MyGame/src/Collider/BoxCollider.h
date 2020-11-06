#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H
#include "SDL.h"
#include <string>
#include "GameObject.h"
class BoxCollider
{
public:
	BoxCollider();
	void Update(ObjectProperty objProp);
	SDL_Rect GetBoxCollider();
	void Render();
private:
	SDL_Rect objectBox;
};
#endif

