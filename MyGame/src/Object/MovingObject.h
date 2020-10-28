#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H
#include "ObjectProperty.h"
#include "Animation.h"
class MovingObject : public ObjectProperty
{
public:
	MovingObject();
	MovingObject(std::string id, int w, int h);
	inline float GetPositionX() { return objProperty.xPosition; }
	inline float GetPositionY() { return objProperty.yPosition; }
	inline int GetWidth() { return objProperty.width; }
	inline int GetHeight() { return objProperty.height; }
	void UpdatePosX(float x);
	void UpdatePosY(float y);
	inline ObjProperty GetProperties() { return objProperty; };
	virtual void Update();
	virtual void Draw();
	virtual void Clean();
	void SetTexture(std::string id);
protected:
	Animation* animation;
	int animationDelay;
	int direction; // 1=left 2=up 3=right 4=down
};
#endif
