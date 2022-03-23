#include "tile.h"
#include <vector>
#include "xml_lib/tinyxml2.h"
#include "utils.h"

using namespace Engine;


Tile::Tile() {}

Tile::Tile(unsigned int id, bool isWalkable) : Sprite() {
	_id = id;
	_isWalkable = isWalkable;
}

Tile::~Tile() {
	if (!_adyacentTiles.empty()) {

		for (int i = 0; i < _adyacentTiles.size(); i++) {
			if (_adyacentTiles[i])
				_adyacentTiles[i] = nullptr;
		}
		_adyacentTiles.clear();
	}

}

void Tile::SetIsWalkable(bool value) {
	_isWalkable = value;
}

bool Tile::GetIsWalkable() {
	return _isWalkable;
}

unsigned int Tile::GetID() {
	return _id;
}

void Tile::SetID(unsigned int value) {
	_id = value;
}

void Engine::Tile::SetPropertiesPath(const char* path)
{
	tinyxml2::XMLDocument map;
	map.LoadFile(path);

	tinyxml2::XMLElement* Tileset = map.FirstChildElement("tileset");
	if (Tileset) {
		for (tinyxml2::XMLNode* tile = Tileset->FirstChildElement(); tile; tile = tile->NextSiblingElement()) {
			if (tile->ToElement() && tile->ToElement()->IntAttribute("id") && tile->ToElement()->IntAttribute("id") == _id) {
				const char* name = "";
				tinyxml2::XMLElement* properties = tile->FirstChildElement("properties");
				if (properties) {
					tinyxml2::XMLElement* value = properties->FirstChildElement("property");
					if (value) {
						_isWalkable = value->BoolAttribute("value");
						
					}
				}
			}
		}
	}
	map.Clear();
}

void Engine::Tile::SetBottom(Tile* tile)
{
	_adyacentTiles.push_back(tile);
}


void Engine::Tile::SetTop(Tile* tile)
{
	_adyacentTiles.push_back(tile);
}


void Engine::Tile::SetLeft(Tile* tile)
{
	_adyacentTiles.push_back(tile);
}

void Engine::Tile::SetRight(Tile* tile)
{
	_adyacentTiles.push_back(tile);
}


std::vector<Tile*> Engine::Tile::GetAdyacentTiles()
{
	return _adyacentTiles;
}

