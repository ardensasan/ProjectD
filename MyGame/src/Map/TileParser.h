#ifndef TILEPARSER_H
#define TILEPARSER_H
#include <string>
#include <vector>
class MapParser;
struct Tileset {
	int firstID, lastID;
	int rowCount, colCount;
	int tileCount;
	int height, width;
	std::string name, source;
};

struct TileMap {
	int rowCount;
	int colCount;
	std::vector< std::vector<int> > tileMap;
};

class TileParser
{
public:
	TileParser(std::vector<Tileset> tileset, std::vector<TileMap> tilemap);
	void Render();
private:
	std::vector<Tileset> tileSetList;
	std::vector<TileMap> tileMapList;
};
#endif

