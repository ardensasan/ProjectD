#ifndef TILELAYER_H
#define TILELAYER_H
#include <string>
#include <vector>
struct Tileset {
	int firstID, lastID;
	int rowCount, colCount;
	int tileCount;
	int tileHeight, tileWidth;
	std::string name, source;
};


class TileLayer
{
private:
	std::vector<Tileset> vTileSetList;
};
#endif

