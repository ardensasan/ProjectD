#ifndef MAPPARSER_H
#define MAPPARSER_H
#include "tinyxml2.h"
#include "TileLayer.h"
#include <string>
#include <iostream>

class MapParser
{
public:
	static MapParser* GetInstance();
	void Load();
	void Parse(std::string id, std::string filename);
	Tileset ParseTileset(tinyxml2::XMLElement* XMLTileset);
private:
	MapParser();
	static MapParser* instance;
};
#endif

