#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H
#include "TileParser.h"
#include "GameObject.h"
class CollisionHandler
{
public:
	static CollisionHandler* GetInstance();
	bool CheckMapCollision(ObjectProperty objProperty);
	bool CheckMapCollision(ObjectProperty objProperty, int y);
	void Clean();
private:
	CollisionHandler();
	static CollisionHandler* instance;
	float tempXPosition, tempYPosition;
	std::vector<TileMap> tileMapList;
};
#endif

