#include "CollisionHandler.h"
#include "MapParser.h"
#include "SDL.h"

int ignoreTile[] = { 0,40,41,42 }; // tiles to ignore collision on jump
CollisionHandler* CollisionHandler::instance = nullptr;
CollisionHandler::CollisionHandler() {

}

CollisionHandler* CollisionHandler::GetInstance() {
	if (instance == nullptr)
		instance = new CollisionHandler();
	return instance;
}
//horizontal collision handler
bool CollisionHandler::CheckMapCollision(ObjProperty objProperty) {
	SDL_Rect objectRect = { (int)objProperty.xPosition ,(int)objProperty.yPosition , objProperty.width, objProperty.height };
	tileMapList = MapParser::GetInstance()->GetMapLayers();
	for (unsigned int t = 0;t < tileMapList.size();t++) {
		for (int row = 0;row < tileMapList[t].rowCount;row++) {
			for (int col = 0;col < tileMapList[t].colCount;col++) {
				bool isIgnoreTile = std::find(std::begin(ignoreTile), std::end(ignoreTile), tileMapList[t].tileMap[row][col]) != std::end(ignoreTile);
				if (!isIgnoreTile) {
					SDL_Rect tileRect = { row*tileMapList[t].tileWidth, col* tileMapList[t].tileHeight, tileMapList[t].tileWidth-1, tileMapList[t].tileHeight-1 };
					if (SDL_HasIntersection(&objectRect, &tileRect)) {
						return true;
					}

				}
			}
		}
	}
	return false;
}
//vertical collision handler
bool CollisionHandler::CheckMapCollision(ObjProperty objProperty,int y) {
	SDL_Rect objectRect = { (int)objProperty.xPosition ,(int)objProperty.yPosition , objProperty.width, objProperty.height };
	tileMapList = MapParser::GetInstance()->GetMapLayers();
	for (unsigned int t = 0;t < tileMapList.size();t++) {
		for (int row = 0;row < tileMapList[t].rowCount;row++) {
			for (int col = 0;col < tileMapList[t].colCount;col++) {
				if (tileMapList[t].tileMap[row][col] != 0) {
					SDL_Rect tileRect = { row * tileMapList[t].tileWidth, col * tileMapList[t].tileHeight, tileMapList[t].tileWidth - 1, tileMapList[t].tileHeight - 1 };
					bool isIgnoreTile = std::find(std::begin(ignoreTile), std::end(ignoreTile), tileMapList[t].tileMap[row][col]) != std::end(ignoreTile);
					if (y < 0) {
						if (!isIgnoreTile) {
							if (SDL_HasIntersection(&objectRect, &tileRect)) {
								return true;
							}
						}
					}
					else if (y > 0) {
						if (SDL_HasIntersection(&objectRect, &tileRect)) {
							if (isIgnoreTile) {
								if ((objProperty.yPosition + objProperty.height) < (tileRect.y+5))
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