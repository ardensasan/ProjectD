#include "TileParser.h"
#include "TextureManager.h"
TileParser::TileParser(std::vector<Tileset> tilesets, std::vector<TileMap> tilemap) {
	tileSetList = tilesets;
	tileMapList = tilemap;
	for (unsigned int i = 0;i < tilesets.size();i++) {
		TextureManager::GetInstance()->Load(tilesets[i].name, "Assets/Maps/" + tilesets[i].source);
	}
}

void TileParser::Render() {
	for (unsigned int t = 0;t < tileMapList.size();t++) {
		for (int col = 0;col < tileMapList[t].colCount;col++) {
			for (int row = 0;row < tileMapList[t].rowCount;row++) {
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