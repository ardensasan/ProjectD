#include "TileParser.h"
#include "TextureManager.h"
#include "Camera.h"
#include "MapParser.h"
TileParser::TileParser(std::vector<Tileset> tilesets) {
	tileSetList = tilesets;
	for (unsigned int i = 0;i < tilesets.size();i++)
		TextureManager::GetInstance()->Load(tilesets[i].name, "Assets/Maps/" + tilesets[i].source);
}

std::vector<TileMap> TileParser::Update() {
	tileMapList = MapParser::GetInstance()->GetMapLayers();
	for (unsigned int t = 0;t < tileMapList.size();t++) {
		for (int row = 0;row < tileMapList[t].rowCount;row++) {
			for (int col = 0;col < tileMapList[t].colCount;col++) {
				for (unsigned int ts = 0;ts < tileSetList.size();ts++) {
					if (tileMapList[t].tileMap[row][col] >= tileSetList[ts].firstID && tileMapList[t].tileMap[row][col] <= tileSetList[ts].lastID) {
						tileMapList[t].tileWidth = tileSetList[ts].width;
						tileMapList[t].tileHeight = tileSetList[ts].height;
						break;
					}
				}
			}
		}
	}
	return tileMapList;
}

void TileParser::Render() {
	tileMapList = MapParser::GetInstance()->GetMapLayers();
	for (unsigned int t = 0;t < tileMapList.size();t++) {
		for (int row = 0;row < tileMapList[t].rowCount;row++) {
			for (int col = 0;col < tileMapList[t].colCount;col++) {
				for (unsigned int ts = 0;ts < tileSetList.size();ts++) {
					if (tileMapList[t].tileMap[row][col] >= tileSetList[ts].firstID && tileMapList[t].tileMap[row][col] <= tileSetList[ts].lastID) {
						int tileID = tileMapList[t].tileMap[row][col] + tileSetList[ts].tileCount - tileSetList[ts].lastID;
						int tileRow = tileID / tileSetList[ts].colCount;
						int tileCol = tileID - tileRow * tileSetList[ts].colCount - 1;
						if (tileID % tileSetList[ts].colCount == 0) {
							tileRow--;
							tileCol = tileSetList[ts].colCount - 1;
						}
						TextureManager::GetInstance()->DrawTile(tileSetList[ts].name, row, col, tileSetList[ts].width, tileSetList[ts].height, tileRow, tileCol);
						break;
					}
				}
			}
		}
	}
}