#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "core.h"
class Tile
{
	public:
		Tile();
		Tile(const std::string _name, const bool _walkable, const sf::Vector2i _position, const sf::Vector2i _size);
		void print(sf::RenderWindow& _window, float x, float y);
		sf::Sprite m_tile;
		bool m_walkable;
	private :
		int m_xSize;
		int m_ySize;
		std::string m_name;
		//std::string m_src;
		
};

