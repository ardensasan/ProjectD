#include "MapParser.h"
MapParser* MapParser::instance = nullptr;
MapParser::MapParser() {

}

MapParser* MapParser::GetInstance() {
	if (instance == nullptr)
		instance = new MapParser();
	return instance;
}

void MapParser::Load() {
	return Parse("testMap", "assets/Maps/testMap.tmx");
}

void MapParser::Parse(std::string id, std::string source) {
	tinyxml2::XMLDocument xml;
	xml.LoadFile(source.c_str());
	if (xml.Error()) {
		std::cout << "Failed to load: " << source << std::endl;
	}
	std::vector<Tileset> tileSetList;
	tinyxml2::XMLElement* root = xml.RootElement();
	for (tinyxml2::XMLElement* e = root->FirstChildElement();e != nullptr;e = e->NextSiblingElement()) {
		if (e->Value() == std::string("tileset")) {
			tileSetList.push_back(ParseTileset(e));
		}
	}
	//std::string aw;
	//for (tinyxml2::XMLElement* e = root->FirstChildElement();e != nullptr;e = e->NextSiblingElement()) {
	//	if (e->Value() == std::string("layer")) {
	//		rowcount = atoi(e->Attribute("width"));
	//		colcount = atoi(e->Attribute("height"));
	//		aw = e->FirstChildElement()->GetText();
	//		std::cout << aw << std::endl;
	//	}
	//}
	////Parse Tile Sets
	//TileSetList tilesets;
	//for (tinyxml2::XMLElement* e = root->FirstChildElement();e != nullptr;e = e->NextSiblingElement()) {
	//	if (e->Value() == std::string("tileset")) {
	//		tilesets.push_back(ParseTileset(e));
	//	}
	//}
	////Parse Layers
	//GameMap* gamemap = new GameMap();
	//for (tinyxml2::XMLElement* e = root->FirstChildElement();e != nullptr;e = e->NextSiblingElement()) {
	//	if (e->Value() == std::string("layer")) {
	//		TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
	//		gamemap->vMapLayers.push_back(tilelayer);
	//	}
	//}
	//mapDict[id] = gamemap;
	//return true;
}

Tileset MapParser::ParseTileset(tinyxml2::XMLElement* XMLTileset) {
	Tileset tileset;
	tileset.name = XMLTileset->Attribute("name");
	tileset.firstID = atoi(XMLTileset->Attribute("firstgid"));
	tileset.tileCount = atoi(XMLTileset->Attribute("tilecount"));
	tileset.lastID = (tileset.firstID + tileset.tileCount) - 1;
	tileset.colCount = atoi(XMLTileset->Attribute("columns"));
	tileset.rowCount = tileset.tileCount / tileset.colCount;
	tileset.tileWidth = atoi(XMLTileset->Attribute("tilewidth"));
	tileset.tileHeight = atoi(XMLTileset->Attribute("tileheight"));
	XMLTileset = XMLTileset->FirstChildElement();
	tileset.source = XMLTileset->Attribute("source");
	return tileset;

}