	#include "tilemap.h"
#include "collision_manager.h"
#include "tile.h"
#include "xml_lib/tinyxml2.h"	
#include <sstream>
#include "texture_importer.h"
#include "utils.h"
#include "renderer.h"

using namespace Engine;

Tilemap::Tilemap(glm::ivec2 dimensions, Shader shader, const char* imagePath, Renderer* renderer) {
	dims = dimensions;
	this->shader = shader;
	this->imagePath = imagePath;
	_renderer = renderer;
	_texture = new TextureImporter();
}

Tilemap::~Tilemap() {
	if (!grid.empty()) {
		grid.clear();
	}
	if (!tiles.empty()){
		for (int i = 0; i < tiles.size(); i++) {
			for (int j = 0; j < tiles[i].size(); j++) {
				for (int k = 0; k < tiles[i][j].size(); k++) {
					if (tiles[i][j][k]) {
						delete tiles[i][j][k];
						tiles[i][j][k] = nullptr;
					}
				}
			}
		}
		tiles.clear();
	}
	if (_texture != NULL) {
		delete _texture;
		_texture = NULL;
	}
}

void Tilemap::SetImagePath(const char* imagepath){
	this->imagePath = imagepath;
}

void Tilemap::LoadMap(const char* path) {
	tinyxml2::XMLDocument map;
	map.LoadFile(path);
	tinyxml2::XMLElement* mapElements = map.FirstChildElement("map");
	if (mapElements == NULL) {
		std::cout << "Error loading tilemap" << std::endl;
		return;
	}
	int width = mapElements->IntAttribute("width");
	int height = mapElements->IntAttribute("height");
	_tileWidth = mapElements->IntAttribute("tilewidth");
	_tileHeight = mapElements->IntAttribute("tileheight");

	int layers = 0;
	std::vector<tinyxml2::XMLElement*>layerElement;
	for (tinyxml2::XMLElement* child = mapElements->FirstChildElement(); child; child = child->NextSiblingElement()) {
		string name = child->Name();
		string layer = "layer";
		if (child != NULL && name == layer) {
			layers++;
			layerElement.push_back(child);
		}
	}
	std::cout << layers << std::endl;
	grid.resize(layers);
	for (int l = 0; l < grid.size(); l++) {
		tinyxml2::XMLText* dataElement = layerElement[l]->FirstChildElement("data")->FirstChild()->ToText();
		if (dataElement == NULL) {
			std::cout << "Error loading tilemap" << std::endl;
			return;
		}

		std::string mapGrid;
		mapGrid = dataElement->Value();
		std::stringstream ss(mapGrid);
		grid[l].resize(height);
		for (int y = 0; y < height; y++) {
			grid[l][y].resize(width);
			for (int x = 0; x < width; x++) {
				std::string value;
				std::getline(ss, value, ',');
				if (!ss.good())
					break;

				int val;
				if (std::stringstream(value) >> val)
					grid[l][y][x] = val;

				tilesAmmount++;
			}
		}
	}
	map.Clear();
	LoadTilesFromMap();
	SetAdyacentTiles();
}


void Tilemap::LoadTilesFromMap() {
	_texture->SetPath(imagePath);
	_texture->LoadImage(_imageWidth, _imageHeight, true);
	int xPos = _tileWidth;
	int yPos = 700;
	float z = 0;
	int actualID = 0;
	tiles.resize(grid.size());
	for (int l = 0; l < grid.size(); l++) {
		xPos = _tileWidth;
		yPos = 700;
		tiles[l].resize(grid[l].size());
		for (int y = 0; y < grid[l].size(); y++) {
			tiles[l][y].resize(grid[l][y].size());
			for (int x = 0; x < grid[l][y].size(); x++) {
				Tile* newTile = new Tile(grid[l][y][x], false);
				newTile->SetRenderer(_renderer);
				newTile->SetShader(shader);
				newTile->SetPath(imagePath);
				newTile->Init();
				newTile->Translate(xPos, yPos, z);
				newTile->Scale(_tileWidth, _tileHeight, 1);
				if (newTile->GetID() <= 0 && l > 0) {
					delete newTile;
					newTile = NULL;
					xPos += _tileWidth + _tileWidth;
				}
				else {			
					if (newTile->GetID() > 0 && l > 0)
						newTile->SetID(newTile->GetID() - actualID);
					newTile->SetPropertiesPath("res/tilemap/Ground.tsx");
					newTile->SetUVs(GetTileFromID(newTile->GetID() ));
					tiles[l][y][x] = newTile;
					xPos += newTile->transform.scale.x + _tileWidth;
				}

			}
			z += 0.001f;
			yPos -= _tileHeight + _tileHeight;
			xPos = _tileWidth;
		}
		actualID=1;
	}
	std::cout << "Ammount of tilemap Entities: " << tiles.size() << endl;
}

void Engine::Tilemap::SetAdyacentTiles()
{
	for (int i = 0; i < tiles.size(); i++) {
		for (int j = 0; j < tiles[i].size(); j++) {
			for (int k = 0; k < tiles[i][j].size(); k++) {
				if (tiles[i][j][k]) {
					if ((k-1) >= 0 && tiles[i][j][k -1])tiles[i][j][k]->SetLeft(tiles[i][j][k -1]);

					if ((j-1) >= 0 && tiles[i][j - 1][k])tiles[i][j][k]->SetTop(tiles[i][j-1][k]);

					if ((k+1 < tiles[i][j].size()) && tiles[i][j][k + 1])tiles[i][j][k]->SetRight(tiles[i][j][k + 1]);

					if ((j + 1 < tiles[i][j].size()) && tiles[i][j + 1][k])tiles[i][j][k]->SetBottom(tiles[i][j+1][k]);
				}
			}
		}
	}
}

glm::vec4 Tilemap::GetTileFromID(unsigned int id) {
	int xTile = id % dims.x; // se hace para que cuando el indice sea mayor a la dimension en x, vuelva a ser 0, es decir, se "reinicia" el ciclo en x
	int yTile = id / dims.x;
	yTile = _imageHeight - yTile - 1;
	//                      x  y   w   h
	glm::vec4 uv = glm::vec4(0, 0, 0, 0);

	uv.x = xTile / static_cast<float>(dims.x); // X
	uv.y = yTile / static_cast<float>(dims.y); // Y
	uv.z = 1.0f / (dims.x); // Ancho / W
	uv.w = 1.0f / (dims.y); // Alto / H

	return uv;
}

void Tilemap::Draw() {
	if (!tiles.empty()) {
		for (int i = 0; i < tiles.size(); i++) {
			for (int j = 0; j < tiles[i].size(); j++) {
				for (int k = 0; k < tiles[i][j].size(); k++) {
					if (tiles[i][j][k]) {
						tiles[i][j][k]->DrawSprite();
					}
				}
			}
		}
	}
}

void Tilemap::CheckCollisionWithTileMap(Entity2D* player, glm::vec3 actualPosition, float speed) {



	/*for (int i = 0; i < tiles.size(); i++) {

		if (tiles[i] && !tiles[i]->GetIsWalkable()) {
			collisionManager->CheckCollision(player, tiles[i], speed);
		}
	}*/
	for (int i = 0; i < tiles.size(); i++) {
		for (int j = 0; j < tiles[i].size(); j++) {
			for (int k = 0; k < tiles[i][j].size(); k++) {
				if (tiles[i][j][k] && currentTile != tiles[i][j][k] && collisionManager->CheckTrigger(player, tiles[i][j][k])) {
					currentTile = tiles[i][j][k];
				}
			}
		}
	}
	if (currentTile!=nullptr && currentTile->GetIsWalkable()) {
		for (Tile* tile : currentTile->GetAdyacentTiles()) {
			if (tile && !tile->GetIsWalkable()) {
				collisionManager->CheckCollision(player, tile, speed);
			}
		}
	}
	else {
		if(currentTile)
			collisionManager->CheckCollision(player, currentTile, speed);
	}
}