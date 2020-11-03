#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H
#include "SDL.h"
#include <string>
#include "GameObject.h"
class BoxCollider
{
public:
	BoxCollider();
	BoxCollider(ObjectProperty objProp);
	void Update(float x, float y, int w, int h, std::string name);
	SDL_Rect GetBoxCollider();
	void Render();
private:
	SDL_Rect objectBox;
};
#endif

