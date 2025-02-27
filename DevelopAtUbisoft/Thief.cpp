#include "Thief.h"
#include "TileMap.h"
#include "Game.h"
#include <iostream>
#include "MathUtils.h"


Thief::Thief(const float speed, const uint _xPosition, const uint _yPosition)
	: m_speed(speed)
	, m_tilePosX(_xPosition)
	, m_tilePosY(_yPosition)
{
	m_pv = 5;
	m_sprite = sf::Sprite(Game::get().getThiefTexture(), sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(16,16)));
	m_sprite.setPosition(m_tilePosX *TileMap::TILE_SIZE, m_tilePosY * TileMap::TILE_SIZE);
	m_moneyStolen = 10.f;
}

void Thief::update(float _deltaTime)
{
	const sf::Vector2f& currentPosition = m_sprite.getPosition();
	uint indexTargetPosX = m_tilePosX;
	uint indexTargetPosY = m_tilePosY;
	
	if (m_tilePosX > 0 && TileMap::getTileAt(m_tilePosX -1, m_tilePosY) == WALKABLE) {
		indexTargetPosX = m_tilePosX - 1;
	}else if (m_tilePosY > 0 && TileMap::getTileAt(m_tilePosX, m_tilePosY -1) == WALKABLE) {
		indexTargetPosY = m_tilePosY - 1;
	}

	const bool hasArrived = m_tilePosX == indexTargetPosX && m_tilePosY == indexTargetPosY;
	
	if (hasArrived)	{
		return;
	}
	
	sf::Vector2f targetPosition{indexTargetPosX * TileMap::TILE_SIZE, indexTargetPosY * TileMap::TILE_SIZE };
	sf::Vector2f direction{ targetPosition - currentPosition };
	float dist = math::norm(direction);
	direction = math::normalize(direction);
	
	if (dist < DEST_EPSILON) {
		m_tilePosX = indexTargetPosX;
		m_tilePosY = indexTargetPosY;
	}

	m_sprite.setPosition({ currentPosition + direction * m_speed * _deltaTime });


	
}

void Thief::draw(sf::RenderWindow& _window)
{
	_window.draw(m_sprite);
}

void Thief::getShot()
{
	m_pv -= 2;
}

