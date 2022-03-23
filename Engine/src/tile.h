#ifndef TILE_H
#define TILE_H
#include "export.h"
#include "sprite.h"
#include <vector>

namespace Engine {

	class ENGINE_API Tile : public Sprite {
	private:
		bool _isWalkable = false;
		unsigned int _id = 0;
		std::vector<Tile*> _adyacentTiles;

	public:
		Tile();
		Tile(unsigned int id, bool isWalkable);
		~Tile();
		void SetIsWalkable(bool value);
		bool GetIsWalkable();
		unsigned int GetID();
		void SetID(unsigned int value);
		void SetPropertiesPath(const char* path);
		void SetBottom(Tile* tile);
		void SetTop(Tile* tile);
		void SetLeft(Tile* tile);
		void SetRight(Tile* tile);
		std::vector<Tile*> GetAdyacentTiles();
	};

}
#endif // !TILE_H
