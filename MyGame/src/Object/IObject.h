#ifndef IOBJECT_H
#define IOBJECT_H
#include "SDL.h"
class IObject {
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;
};
#endif;