#include "Tile.h"
#include "Game.h"
#include "TileMap.h"
Tile::Tile()
	: m_name("")
	, m_walkable(false)
	, m_tile()
{
	m_xSize = 0;
	m_ySize = 0;
}
Tile::Tile(const std::string _name, const bool _walkable, const sf::Vector2i _position, const sf::Vector2i _size)
	: m_name(_name)
	, m_walkable(_walkable)
{	
	m_xSize = _size.x*TileMap::TILE_SCALE; 
	m_ySize = _size.y* TileMap::TILE_SCALE;
	m_tile = sf::Sprite(Game::get().getTexture(),sf::IntRect(_position,_size));
	m_tile.setScale(sf::Vector2f(TileMap::TILE_SCALE, TileMap::TILE_SCALE));
}

void Tile::print(sf::RenderWindow& _window,float x, float y) {
	m_tile.setPosition(x* this->m_xSize, y * this->m_ySize);
	_window.draw(m_tile);
}