#ifndef TILEPARSER_H
#define TILEPARSER_H
#include "SDL.h"
#include <string>
#include <vector>
#include <map>
class MapParser;
struct Tileset {
	int firstID, lastID;
	int rowCount, colCount;
	int tileCount;
	int height, width;
	std::string name, source;
};

struct TileMap {
	int tileWidth, tileHeight;
	std::string layerName;
	int rowCount;
	int colCount;
	std::vector< std::vector<int> > tileMap;
};

class TileParser
{
public:
	TileParser(std::vector<Tileset> tileset);
	std::vector<TileMap> Update();
	void Render();
private:
	std::vector<Tileset> tileSetList;
	std::vector<TileMap> tileMapList;
};
#endif

