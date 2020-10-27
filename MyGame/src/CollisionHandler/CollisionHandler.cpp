#include "CollisionHandler.h"
#include "MapParser.h"
#include "SDL.h"
CollisionHandler* CollisionHandler::instance = nullptr;
CollisionHandler::CollisionHandler() {

}

CollisionHandler* CollisionHandler::GetInstance() {
	if (instance == nullptr)
		instance = new CollisionHandler();
	return instance;
}

bool CollisionHandler::CheckMapCollision(ObjProperty objProperty) {
	SDL_Rect objectRect = { objProperty.xPosition ,objProperty.yPosition , objProperty.width, objProperty.height };
	tileMapList = MapParser::GetInstance()->GetMapLayers();
	for (unsigned int t = 0;t < tileMapList.size();t++) {
		for (unsigned int row = 0;row < tileMapList[t].rowCount;row++) {
			for (unsigned int col = 0;col < tileMapList[t].colCount;col++) {
				if (tileMapList[t].tileMap[row][col] != 0) {
					SDL_Rect tileRect = { row*tileMapList[t].tileWidth, col* tileMapList[t].tileHeight, tileMapList[t].tileWidth, tileMapList[t].tileHeight };
					if (SDL_HasIntersection(&objectRect, &tileRect)) {
						return true;
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