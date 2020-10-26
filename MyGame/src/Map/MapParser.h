#ifndef MAPPARSER_H
#define MAPPARSER_H
#include "tinyxml2.h"
#include "TileParser.h"
#include "GameMap.h"
#include <string>
#include <iostream>
#include <map>
class MapParser
{
public:
	static MapParser* GetInstance();
	bool Load();
	bool Parse(std::string id, std::string filename);
	Tileset ParseTileset(tinyxml2::XMLElement* XMLTileset);
	TileMap ParseTileLayer(tinyxml2::XMLElement* XMLTileset);
	std::vector<TileMap> GetMapLayers() { return gamemap->mapLayers; };
	void UpdateTileMaps(std::vector<TileMap> tilemaps);
	void Render();
	void Clean();
private:
	MapParser();
	GameMap* gamemap;
	static MapParser* instance;
};
#endif

