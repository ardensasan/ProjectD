#include "MapParser.h"
#include "TextureManager.h"
#include <sstream>
#include "Engine.h"
TileParser* tileparser;
MapParser* MapParser::instance = nullptr;
GameMap* gamemap;
MapParser::MapParser() {
	movingObject = "MovingObjects";
	staticObject = "StaticObjects";
}

MapParser* MapParser::GetInstance() {
	if (instance == nullptr)
		instance = new MapParser();
	return instance;
}

bool MapParser::Load() {
	staticObjectList.clear();
	movingObjectList.clear();
	return Parse("Map1", "assets/Maps/Map1.tmx");
}

bool MapParser::Parse(std::string id, std::string source) {
	tinyxml2::XMLDocument xml;
	xml.LoadFile(source.c_str());
	if (xml.Error()) {
		std::cout << "Failed to load: " << source << std::endl;
		return false;
	}
	//Parse tilesets
	std::vector<Tileset> tilesets;
	tinyxml2::XMLElement* root = xml.RootElement();
	for (tinyxml2::XMLElement* e = root->FirstChildElement();e != nullptr;e = e->NextSiblingElement()) {
		if (e->Value() == std::string("tileset")) {
			tilesets.push_back(ParseTileset(e));
		}
	}
	
	//Parse tile layers
	std::vector<TileMap> tilemaps;
	for (tinyxml2::XMLElement* e = root->FirstChildElement();e != nullptr;e = e->NextSiblingElement()) {
		if (e->Value() == std::string("layer")) {
			tilemaps.push_back(ParseTileLayer(e));
		}
	}
	tileparser = new TileParser(tilesets);
	gamemap = new GameMap();
	gamemap->mapLayers = tilemaps;
	gamemap->mapLayers = tileparser->Update();
	//update tilemaps to match tileset properties
	std::string aw = "";
	for (tinyxml2::XMLElement* e = root->FirstChildElement();e != nullptr;e = e->NextSiblingElement()) {
		if (e->Value() == std::string("objectgroup")) {
			if (e->Attribute("name") == staticObject) {
				staticObjectList = ParseObjects(e);
			}
			else if (e->Attribute("name") == movingObject) {
				movingObjectList = ParseObjects(e);
			}
		}
	}
	return true;
}

std::vector <ObjectProperty> MapParser::ParseObjects(tinyxml2::XMLElement* XMLObject) {
	std::vector<ObjectProperty> objPropList;
	for (tinyxml2::XMLElement* e = XMLObject->FirstChildElement("object");e != nullptr;e = e->NextSiblingElement()) {
		ObjectProperty objProp;
		objProp.textureID = e->Attribute("name");
		objProp.type = e->Attribute("type");
		objProp.xPosition = atoi(e->Attribute("x"));
		objProp.yPosition = atoi(e->Attribute("y"));
		objProp.width = atoi(e->Attribute("width"));
		objProp.height = atoi(e->Attribute("height"));
		objPropList.push_back(objProp);
	}
	return objPropList;
}


Tileset MapParser::ParseTileset(tinyxml2::XMLElement* XMLTileset) {
	Tileset tileset;
	tileset.name = XMLTileset->Attribute("name");
	tileset.firstID = atoi(XMLTileset->Attribute("firstgid"));
	tileset.tileCount = atoi(XMLTileset->Attribute("tilecount"));
	tileset.lastID = (tileset.firstID + tileset.tileCount) - 1;
	tileset.colCount = atoi(XMLTileset->Attribute("columns"));
	tileset.rowCount = tileset.tileCount / tileset.colCount;
	tileset.width = atoi(XMLTileset->Attribute("tilewidth"));
	tileset.height = atoi(XMLTileset->Attribute("tileheight"));
	XMLTileset = XMLTileset->FirstChildElement();
	tileset.source = XMLTileset->Attribute("source");
	return tileset;
}

TileMap MapParser::ParseTileLayer(tinyxml2::XMLElement* XMLLayer) {
	TileMap tilemap;
	//Resize vector according to layer row and column
	tilemap.layerName = XMLLayer->Attribute("name");
	tilemap.rowCount = atoi(XMLLayer->Attribute("width"));
	tilemap.colCount = atoi(XMLLayer->Attribute("height"));
	tilemap.tileMap.resize(tilemap.rowCount, std::vector<int>(tilemap.colCount));
	//Search for xml data child
	tinyxml2::XMLElement* data = nullptr;
	for (tinyxml2::XMLElement* e = XMLLayer->FirstChildElement();e != nullptr;e = e->NextSiblingElement()) {
		if (e->Value() == std::string("data")) {
			int x, y;
			x = y = 0;
			std::istringstream ss(e->GetText());
			std::string token;
			//store into vector
			while (std::getline(ss, token, ',')) {
				tilemap.tileMap[y][x] = stoi(token);
				y++;
				if (y == tilemap.rowCount) {
					y = 0;
					x++;
				}
			}
			break;
		}
	}
	return tilemap;
}


void MapParser::Render() {
	tileparser->Render();
}


void MapParser::Clean() {
}
