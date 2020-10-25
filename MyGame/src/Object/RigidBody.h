#ifndef RIGIDBODY_H
#define RIGIDBODY_H
class RigidBody
{
public:
	RigidBody();
	inline int GetPositionX() { return xPos; }
	inline int GetPositionY() { return yPos; }
	inline void MovePosX(int x) { xPos += x; }
	inline void MovePosY(int y) { yPos += y; }
private:
	int xPos,yPos;
};

#endif

