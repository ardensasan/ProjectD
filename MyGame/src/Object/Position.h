#ifndef POSITION_H
#define POSITION_H
class Position
{
public:
	Position();
	inline int GetPositionX() { return (int)xPos; }
	inline int GetPositionY() { return (int)yPos; }
	inline void UpdatePosX(float x) { xPos += x; }
	inline void UpdatePosY(float y) { yPos += y; }
private:
	float xPos,yPos;
};

#endif

