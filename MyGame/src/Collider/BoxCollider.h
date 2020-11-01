#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H
#include "SDL.h"
class BoxCollider
{
public:
	BoxCollider();
	void Render();
	void Update(float x, float y, int w, int h);
private:
	SDL_Rect objectBox;
};
#endif

