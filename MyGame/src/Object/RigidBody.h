#ifndef RIGIDBODY_H
#define RIGIDBODY_H
class RigidBody
{
public:
	RigidBody();
	inline int GetPositionX() { return (int)xPos; }
	inline int GetPositionY() { return (int)yPos; }
	inline void MovePosX(float x) { xPos += x; }
	inline void MovePosY(float y) { yPos += y; }
private:
	float xPos,yPos;
};

#endif

