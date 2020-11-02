#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H
#include "SDL.h"
class BoxCollider
{
public:
	BoxCollider();
	void Update(float x, float y, int w, int h);
	inline SDL_Rect GetBoxCollider() { return objectBox; };
	void Render();
private:
	SDL_Rect objectBox;
};
#endif

