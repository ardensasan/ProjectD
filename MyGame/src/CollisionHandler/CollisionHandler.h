#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H
#include "TileParser.h"
#include "GameObject.h"
class CollisionHandler
{
public:
	static CollisionHandler* GetInstance();
	bool CheckObjectMapCollision(SDL_Rect boxCollider, int movemenDirection); // 1 = left, 2 = up, 3 = right, 4 = down
	bool CheckCollisionToObject(SDL_Rect playerRect, SDL_Rect objectRect);
	void Clean();
private:
	CollisionHandler();
	static CollisionHandler* instance;
	float tempXPosition, tempYPosition;
	std::vector<TileMap> tileMapList;
};
#endif

