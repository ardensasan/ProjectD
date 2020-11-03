#ifndef MAPPARSER_H
#define MAPPARSER_H
#include "tinyxml2.h"
#include "TileParser.h"
#include "GameMap.h"
#include "GameObject.h"
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
	TileMap ParseTileLayer(tinyxml2::XMLElement* XMLLayer);
	std::vector <ObjectProperty> ParseObjects(tinyxml2::XMLElement* XMLObject);
	std::vector<TileMap> GetMapLayers() { return gamemap->mapLayers; };
	inline std::vector<ObjectProperty> GetStaticObjects() { return staticObjectList; }
	inline std::vector<ObjectProperty> GetMovingObjects() { return movingObjectList; }
	void Render();
	void Clean();
private:
	MapParser();
	GameMap* gamemap;
	static MapParser* instance;
	std::vector <ObjectProperty> staticObjectList;
	std::vector <ObjectProperty> movingObjectList;
	std::string movingObject; // moving object xml equivalent string
	std::string staticObject;// static object xml equivalent string
};
#endif

