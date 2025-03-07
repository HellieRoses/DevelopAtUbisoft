#include "Thief.h"
#include "TileMap.h"
#include "Game.h"
#include <iostream>
#include "MathUtils.h"


Thief::Thief( const uint _xPosition, const uint _yPosition)
	: m_tilePosX(_xPosition)
	, m_tilePosY(_yPosition)
{
	m_speed = THIEF_SPEED;
	m_pv = 5;
	m_sprite = sf::Sprite(Game::get().getThiefTexture(), sf::IntRect(sf::Vector2i(THIEF_BASE_SPRITE_SIZE *17, 0), sf::Vector2i(THIEF_BASE_SPRITE_SIZE, MAX_BASE_TILE_SIZE)));
	m_sprite.setPosition(m_tilePosX * MINI_TILE_SIZE, m_tilePosY * MINI_TILE_SIZE);
	m_sprite.setOrigin(THIEF_ORIGIN, THIEF_ORIGIN);
	m_sprite.setScale({ MAX_SCALE,MAX_SCALE });
	m_moneyStolen = 10.f;
}

bool Thief::isDead() 
{
	if (m_pv <= 0) {
		wantDestroy = true;
		return true;
	}
	return false;
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
	
	sf::Vector2f targetPosition{indexTargetPosX * MINI_TILE_SIZE, indexTargetPosY * MINI_TILE_SIZE };
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
	m_pv -= 3;
	isDead();
}

void Thief::getShotByMissile()
{
	m_pv -= m_pv;
	isDead();
}

