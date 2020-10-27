#ifndef OBJECTPROPERTY_H
#define OBJECTPROPERTY_H
#include <string>
struct ObjProperty {
	std::string textureID;
	float xPosition;
	float yPosition;
	int width;
	int height;
};
class ObjectProperty
{
public:
	ObjProperty objProperty;
	ObjectProperty();
	inline float GetPositionX() { return objProperty.xPosition; }
	inline float GetPositionY() { return objProperty.yPosition; }
	inline int GetWidth() { return objProperty.width; }
	inline int GetHeight() { return objProperty.height; }
	void UpdatePosX(float x);
	void UpdatePosY(float y);
	inline ObjProperty GetProperties() { return objProperty; };

private:
};

#endif

