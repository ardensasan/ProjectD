#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <vector>
#include "TileParser.h"
class GameMap {
public:
	GameMap() {};
	void Render();
	void Update(std::vector<TileMap> tilemap);
	std::vector<TileMap> GetMapLayer() { return mapLayers; };
private:
	friend class MapParser;
	std::vector<TileMap> mapLayers;
};
#endif

