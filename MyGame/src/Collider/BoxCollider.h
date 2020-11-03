#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H
#include "SDL.h"
#include <string>
class BoxCollider
{
public:
	BoxCollider();
	void Update(float x, float y, int w, int h, std::string name);
	inline SDL_Rect GetBoxCollider() { return objectBox; };
	void Render();
private:
	SDL_Rect objectBox;
};
#endif

