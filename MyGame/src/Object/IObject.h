#ifndef IOBJECT_H
#define IOBJECT_H
#include "SDL.h"
class IObject {
public:
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;
};
#endif;