#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H
#include "TileParser.h"
#include "GameObject.h"
class CollisionHandler
{
public:
	static CollisionHandler* GetInstance();
	bool CheckObjectMapCollision(ObjectProperty objProperty, int movemenDirection); // 1 = left, 2 = up, 3 = right, 4 = down
	void Clean();
private:
	CollisionHandler();
	static CollisionHandler* instance;
	float tempXPosition, tempYPosition;
	std::vector<TileMap> tileMapList;
};
#endif

