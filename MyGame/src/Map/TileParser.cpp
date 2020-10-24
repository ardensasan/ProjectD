#include "TileParser.h"
#include "TextureManager.h"
TileParser::TileParser(std::vector<Tileset> tilesets) {
	tilesetList = tilesets;
	for (unsigned int i = 0;i < tilesets.size();i++) {
		TextureManager::GetInstance()->Load(tilesets[i].name, "Assets/Maps/" + tilesets[i].source);
	}
}

void TileParser::Render() {
	//for (unsigned int i = 0;i < iRowCount;i++) {
	//	for (unsigned int j = 0;j < iColCount;j++) {
	//		tileID = tileMap[i][j];
	//		if (tileSets.size() > 1) {
	//			for (unsigned int k = 0;k < tileSets.size();k++) {
	//				if (tileID > tileSets[k].firstID && tileID < tileSets[k].lastID) {
	//					tileID = tileID + tileSets[k].tileCount - tileSets[k].lastID;
	//					index = k;
	//					break;
	//				}
	//			}
	//		}
	//		Tileset ts = tileSets[index];
	//		int tileRow = tileID / ts.colCount;
	//		int tileCol = tileID - tileRow * ts.colCount - 1;
	//		if (tileID % ts.colCount == 0) {
	//			tileRow--;
	//			tileCol = ts.colCount - 1;
	//		}
	//		TextureManager::GetInstance()->DrawTile(ts.name, ts.tileSize, j * ts.tileSize, i * ts.tileSize, tileRow, tileCol);
	//	}
	//}
}