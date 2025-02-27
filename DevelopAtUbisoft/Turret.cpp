#include "Turret.h"
#include "Game.h"
#include "TileMap.h"
Turret::Turret(const uint _xPosition, const uint _yPosition)
	: m_tilePosX(_xPosition)
	, m_tilePosY(_yPosition)
{
	m_topSprite = sf::Sprite(Game::get().getTurret1Texture(), sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(TEXTURE_SIZE, TEXTURE_SIZE)));
	m_baseSprite = sf::Sprite(Game::get().getBaseTurretTexture(), sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(TEXTURE_SIZE, TEXTURE_SIZE)));
	float scale = TileMap::TILE_SIZE / TEXTURE_SIZE;
	m_topSprite.setScale({scale,scale});
	m_baseSprite.setScale({ scale,scale });
	float posX = m_tilePosX * TileMap::TILE_SIZE;
	float posY = m_tilePosY * TileMap::TILE_SIZE;
	m_topSprite.setPosition(posX,posY);
	m_baseSprite.setPosition(posX, posY);
}

void Turret::update(float _deltaTime)
{
}

void Turret::draw(sf::RenderWindow& _window)
{
	_window.draw(m_baseSprite);
	_window.draw(m_topSprite);
}
