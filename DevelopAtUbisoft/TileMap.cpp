#include "TileMap.h"
#include "Game.h"
#include <iostream>
#include <sstream>

std::array<std::array<int, TILE_X_MAX>, TILE_Y_MAX> TileMap::m_map = { {
		{CORNERUL,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,BORDERUP,CORNERUR},
		{INTERIORW,INTERIORW,INTERIORW,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,BORDERRIGHT},
		{BORDERLEFT,INTERIOR,INTERIORW,INTERIORW,INTERIORW,INTERIORW,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,BORDERRIGHT},
		{BORDERLEFT,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIORW,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,BORDERRIGHT},
		{BORDERLEFT,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIORW,INTERIORW,INTERIORW,INTERIORW,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,BORDERRIGHT},
		{BORDERLEFT,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIORW,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,BORDERRIGHT},
		{BORDERLEFT,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIORW,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,BORDERRIGHT},
		{BORDERLEFT,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIORW,INTERIORW,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,BORDERRIGHT},
		{BORDERLEFT,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIORW,INTERIORW,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,BORDERRIGHT},
		{BORDERLEFT,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIORW,INTERIORW,INTERIORW,INTERIORW,INTERIORW,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,BORDERRIGHT},
		{BORDERLEFT,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIORW,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,BORDERRIGHT},
		{BORDERLEFT,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIORW,INTERIORW,INTERIORW,INTERIORW,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,BORDERRIGHT},
		{BORDERLEFT,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIORW,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,BORDERRIGHT},
		{BORDERLEFT,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIORW,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,BORDERRIGHT},
		{BORDERLEFT,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIORW,INTERIORW,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,BORDERRIGHT},
		{BORDERLEFT,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIORW,INTERIORW,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,BORDERRIGHT},
		{BORDERLEFT,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIOR,INTERIORW,INTERIORW,INTERIORW,INTERIORW,INTERIORW,INTERIORW,INTERIORW,INTERIORW,INTERIORW,INTERIORW},
		{CORNERDL,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,BORDERDOWN,CORNERDR}
	} };

const sf::Vector2i TileMap::TILE_INT_RECT { MINI_BASE_TILE_SIZE ,MINI_BASE_TILE_SIZE };

const sf::Vector2u TileMap::TILE_START_THIEF{ TILE_THIEF_START_X,TILE_THIEF_START_Y };
const sf::Vector2u TileMap::TILE_END_THIEF{ TILE_THIEF_END_X,TILE_THIEF_END_Y };
uint TileMap::getTileAt(uint x, uint y)
{
	return m_map[y][x];
}

/*This class is a work in progress because I don't have all of the sprite required for my game*/
TileMap::TileMap()
{
}

void TileMap::loadTiles() {
	//here if is null do: 
	//m_interiorTile = std::make_unique<Tile>("interior", false, sf::Vector2i(30* MINI_BASE_TILE_SIZE, 0), TILE_INT_RECT);
	//m_interiorWalkableTile = std::make_unique<Tile>("interiorW", true, sf::Vector2i(30 * MINI_BASE_TILE_SIZE, 0), TILE_INT_RECT);
	//m_BUTile = std::make_unique<Tile>("borderup", false, sf::Vector2i(26 * MINI_BASE_TILE_SIZE, 0), TILE_INT_RECT);
	//m_BDTile = std::make_unique<Tile>("borderdown", false, sf::Vector2i(26 * MINI_BASE_TILE_SIZE, MINI_BASE_TILE_SIZE), TILE_INT_RECT);
	//m_BLTile = std::make_unique<Tile>("borderleft", false, sf::Vector2i(27 * MINI_BASE_TILE_SIZE, 0), TILE_INT_RECT);
	//m_BRTile = std::make_unique<Tile>("borderright", false, sf::Vector2i(27 * MINI_BASE_TILE_SIZE, MINI_BASE_TILE_SIZE), TILE_INT_RECT);
	//m_CULTile = std::make_unique<Tile>("cornerupleft", false, sf::Vector2i(24 * MINI_BASE_TILE_SIZE, 0), TILE_INT_RECT);
	//m_CURile = std::make_unique<Tile>("cornerupright", false, sf::Vector2i(25 * MINI_BASE_TILE_SIZE, 0), TILE_INT_RECT);
	//m_CDLile = std::make_unique<Tile>("cornerdownleft", false, sf::Vector2i(24 * MINI_BASE_TILE_SIZE, MINI_BASE_TILE_SIZE), TILE_INT_RECT);
	//m_CDRile = std::make_unique<Tile>("cornerdownright", false, sf::Vector2i(25 * MINI_BASE_TILE_SIZE, MINI_BASE_TILE_SIZE), TILE_INT_RECT);

	m_interiorTile = std::make_unique<Tile>("interior", false, sf::Vector2i(0,9* MINI_BASE_TILE_SIZE), TILE_INT_RECT);
	m_interiorWalkableTile = std::make_unique<Tile>("interiorW", true, sf::Vector2i(10*MINI_BASE_TILE_SIZE, 8 * MINI_BASE_TILE_SIZE), TILE_INT_RECT);
	m_BUTile = std::make_unique<Tile>("borderup", false, sf::Vector2i(3*MINI_BASE_TILE_SIZE, 8 * MINI_BASE_TILE_SIZE), TILE_INT_RECT);
	m_BDTile = std::make_unique<Tile>("borderdown", false, sf::Vector2i(3 * MINI_BASE_TILE_SIZE, 8 * MINI_BASE_TILE_SIZE), TILE_INT_RECT);
	m_BLTile = std::make_unique<Tile>("borderleft", false, sf::Vector2i(3 * MINI_BASE_TILE_SIZE, 8 * MINI_BASE_TILE_SIZE), TILE_INT_RECT);
	m_BRTile = std::make_unique<Tile>("borderright", false, sf::Vector2i(3 * MINI_BASE_TILE_SIZE, 8 * MINI_BASE_TILE_SIZE), TILE_INT_RECT);
	m_CULTile = std::make_unique<Tile>("cornerupleft", false, sf::Vector2i(3 * MINI_BASE_TILE_SIZE, 8 * MINI_BASE_TILE_SIZE), TILE_INT_RECT);
	m_CURile = std::make_unique<Tile>("cornerupright", false, sf::Vector2i(3 * MINI_BASE_TILE_SIZE, 8 * MINI_BASE_TILE_SIZE), TILE_INT_RECT);
	m_CDLile = std::make_unique<Tile>("cornerdownleft", false, sf::Vector2i(3 * MINI_BASE_TILE_SIZE,  8* MINI_BASE_TILE_SIZE), TILE_INT_RECT);
	m_CDRile = std::make_unique<Tile>("cornerdownright", false, sf::Vector2i(3 * MINI_BASE_TILE_SIZE, 8 * MINI_BASE_TILE_SIZE), TILE_INT_RECT);


}

void TileMap::draw(sf::RenderWindow& _window) {
	float x = 0.f;
	float y = 0.f;
	int a = 0;
	int type;
	for (int row = 0; row < m_map.size(); row++) {
		for (int column = 0; column < m_map[0].size(); column++) {
			type = m_map[row][column];
			Tile tile;
			switch (type) {
				case INTERIOR:
					tile = *TileMap::m_interiorTile;
					break;
				case INTERIORW:
					tile = *TileMap::m_interiorWalkableTile;
					break;
				case BORDERUP:
					tile = *TileMap::m_BUTile;
					break;
				case BORDERDOWN:
					tile = *TileMap::m_BDTile;
					break;
				case BORDERLEFT:
					tile = *TileMap::m_BLTile;
					break;
				case BORDERRIGHT:
					tile = *TileMap::m_BRTile;
					break;
				case CORNERUL:
					tile = *TileMap::m_CULTile;
					break;
				case CORNERUR:
					tile = *TileMap::m_CURile;
					break;
				case CORNERDL:
					tile = *TileMap::m_CDLile;
					break;
				case CORNERDR:
					tile = *TileMap::m_CDRile;
					break;
			}
			tile.print(_window ,x, y);
			if (Game::get().isDrawDebug())
			{
				sf::RectangleShape debugShape;
				debugShape.setPosition({x* MINI_TILE_SIZE,y* MINI_TILE_SIZE });
				debugShape.setOutlineColor(sf::Color::Black);
				debugShape.setFillColor(sf::Color::Transparent);
				debugShape.setOutlineThickness(2.0f);
				debugShape.setSize({ MINI_TILE_SIZE, MINI_TILE_SIZE });
				sf::Text debugTextIndex;
				std::ostringstream stringStream;
				stringStream << x << " " << y; 
				debugTextIndex.setString(stringStream.str());
				debugTextIndex.setFont(Game::get().getFont());
				debugTextIndex.setFillColor(sf::Color::Black);
				debugTextIndex.setCharacterSize(15);
				debugTextIndex.setPosition({ x * MINI_TILE_SIZE + 5,y * MINI_TILE_SIZE +5});
				_window.draw(debugShape);
				_window.draw(debugTextIndex);
			}
			x++;
			a++;
		}
		x = 0;
		y++;
	}
};
