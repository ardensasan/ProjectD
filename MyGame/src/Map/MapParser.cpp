#include "MapParser.h"
#include "TextureManager.h"
#include <sstream>
#include "Engine.h"
MapParser* MapParser::instance = nullptr;
MapParser::MapParser() {

}

MapParser* MapParser::GetInstance() {
	if (instance == nullptr)
		instance = new MapParser();
	return instance;
}

bool MapParser::Load() {
	return Parse("test", "assets/Maps/Map1.tmx");
}

bool MapParser::Parse(std::string id, std::string source) {
	tinyxml2::XMLDocument xml;
	xml.LoadFile(source.c_str());
	if (xml.Error()) {
		std::cout << "Failed to load: " << source << std::endl;
		return false;
	}
	//Parse tilesets
	tinyxml2::XMLElement* root = xml.RootElement();
	for (tinyxml2::XMLElement* e = root->FirstChildElement();e != nullptr;e = e->NextSiblingElement()) {
		if (e->Value() == std::string("tileset")) {
			tileSetList.push_back(ParseTileset(e));
		}
	}
	
	//Parse tile layers
	for (tinyxml2::XMLElement* e = root->FirstChildElement();e != nullptr;e = e->NextSiblingElement()) {
		if (e->Value() == std::string("layer")) {
			tileMapList.push_back(ParseTileLayer(e));
		}
	}
	TileParser* tileParser = new TileParser(tileSetList);
	return true;
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

void MapParser::Clean() {
	tileSetList.clear();
	tileMapList.clear();
}
#include <conio.h>
void MapParser::Render() {
	SDL_Texture *texture = IMG_LoadTexture(Engine::GetInstance()->GetRenderer(), "assets/Player/Fall.png");
	for (unsigned int t = 0;t < tileMapList.size();t++) {
		for (unsigned int col = 0;col < tileMapList[t].colCount;col++) {
			std::cout << "\n";
			for (unsigned int row = 0;row < tileMapList[t].rowCount;row++) {

				//SDL_Rect srcRect = { 0,0,32,32 };
				//SDL_Rect dstRect = { row * 16,col * 16,16,16 };
				//SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 100, 100, 100, 50);
				//SDL_RenderClear(Engine::GetInstance()->GetRenderer());
				//SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), texture, &srcRect, &dstRect);
				//SDL_RenderPresent(Engine::GetInstance()->GetRenderer());
				//std::cout << tileMapList[t].tileMap[row][col] << std::endl;
				//_getch();
				for (unsigned int ts = 0;ts < tileSetList.size();ts++) {
					if (tileMapList[t].tileMap[row][col] >= tileSetList[ts].firstID && tileMapList[t].tileMap[row][col] <= tileSetList[ts].lastID) {
						int tileID = tileMapList[t].tileMap[row][col] + tileSetList[ts].tileCount - tileSetList[ts].lastID;

						int tileRow = tileID / tileSetList[ts].colCount;
						int tileCol = tileID - tileRow * tileSetList[ts].colCount - 1;
						if (tileID % tileSetList[ts].colCount == 0) {
							tileRow--;
							tileCol = tileSetList[ts].colCount - 1;
						}
						TextureManager::GetInstance()->DrawTile(tileSetList[ts].name, row, col, tileSetList[ts].width, tileSetList[ts].height, tileRow, tileCol);
						break;
					}
				}
			}
		}
	}

}
