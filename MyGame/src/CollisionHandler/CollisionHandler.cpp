#include "CollisionHandler.h"
#include "MapParser.h"
#include "SDL.h"

int ignoreTile[] = { 40,41,42 }; // tiles to ignore collision on jump
CollisionHandler* CollisionHandler::instance = nullptr;
CollisionHandler::CollisionHandler() {
}

CollisionHandler* CollisionHandler::GetInstance() {
	if (instance == nullptr)
		instance = new CollisionHandler();
	return instance;
}

//object to map collision
bool CollisionHandler::CheckObjectMapCollision(SDL_Rect boxCollider, int movementDirection) {
	tileMapList = MapParser::GetInstance()->GetMapLayers();
	for (unsigned int t = 0;t < tileMapList.size();t++) {
		for (int row = 0;row < tileMapList[t].rowCount;row++) {
			for (int col = 0;col < tileMapList[t].colCount;col++) {
				if (tileMapList[t].tileMap[row][col] != 0) {
					SDL_Rect tileRect = { (row * tileMapList[t].tileWidth) + 1, (col * tileMapList[t].tileHeight) + 1, tileMapList[t].tileWidth - 1, tileMapList[t].tileHeight - 1 };
					bool isIgnoreTile = std::find(std::begin(ignoreTile), std::end(ignoreTile), tileMapList[t].tileMap[row][col]) != std::end(ignoreTile);
					//upward movement and x axis collision
					if (movementDirection == 2 || movementDirection == 0) {
						if (!isIgnoreTile) {
							if (SDL_HasIntersection(&boxCollider, &tileRect)) {
								return true;
							}
						}
					}
					//downward movement collision
					else if (movementDirection == 4) {
						if (SDL_HasIntersection(&boxCollider, &tileRect)) {
							if (isIgnoreTile) {
								if ((boxCollider.y + boxCollider.h) < (tileRect.y + 5))
									return true;
							}
							else {
								return true;
							}

						}
					}
				}
			}
		}
	}
	return false;
}

void CollisionHandler::Clean() {
	tileMapList.clear();
}