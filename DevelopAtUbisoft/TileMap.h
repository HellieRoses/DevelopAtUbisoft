#pragma once
#include "Tile.h"
#include <array>
#include <string>
#include <memory>
#include "core.h"
#define INTERIOR 0
#define INTERIORW 1
#define BORDERUP 2
#define BORDERDOWN 3
#define BORDERLEFT 4
#define BORDERRIGHT 5 
#define CORNERUL 6
#define CORNERUR 7
#define CORNERDL 8
#define CORNERDR 9
class TileMap
{
	public:
		TileMap();
		void loadTiles();
		void draw(sf::RenderWindow& _window);
		static constexpr int TILE_BASE_SIZE = 16;
		static constexpr float TILE_SCALE = 2.f;
		static constexpr float TILE_SIZE = TILE_BASE_SIZE*TILE_SCALE;
		static const TileCoord TILE_START_THIEF;
		static const TileCoord TILE_END_THIEF;
		static uint getTileAt(uint x, uint y);
	private :
		static std::array<std::array<int, 10>, 8> m_map;
		std::unique_ptr<Tile> m_interiorTile;
		std::unique_ptr<Tile> m_interiorWalkableTile;
		std::unique_ptr<Tile> m_BUTile;
		std::unique_ptr<Tile> m_BDTile;
		std::unique_ptr<Tile> m_BLTile;
		std::unique_ptr<Tile> m_BRTile;
		std::unique_ptr<Tile> m_CULTile;
		std::unique_ptr<Tile> m_CURile;
		std::unique_ptr<Tile> m_CDLile;
		std::unique_ptr<Tile> m_CDRile;

};

