#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H
#include "ObjectProperty.h"
#include "TileParser.h"
class CollisionHandler
{
public:
	static CollisionHandler* GetInstance();
	bool CheckMapCollision(ObjProperty objProperty);
	bool CheckMapCollision(ObjProperty objProperty, int y);
	void Clean();
private:
	CollisionHandler();
	static CollisionHandler* instance;
	float tempXPosition, tempYPosition;
	std::vector<TileMap> tileMapList;
};
#endif
