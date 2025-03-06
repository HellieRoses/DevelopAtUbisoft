#include "Turret.h"
#include "Game.h"
#include "TileMap.h"
#include "MathUtils.h"
#include "Thief.h"
#include "Missile.h"
#include <iostream>
Turret::Turret(const uint _xPosition, const uint _yPosition)
	: m_tilePosX(_xPosition)
	, m_tilePosY(_yPosition)
{
	m_topSprite = sf::Sprite(Game::get().getTurret1Texture(), sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(TEXTURE_SIZE, TEXTURE_SIZE)));
	m_baseSprite = sf::Sprite(Game::get().getBaseTurretTexture(), sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(TEXTURE_SIZE, TEXTURE_SIZE)));
	float scale = TileMap::TILE_SIZE / TEXTURE_SIZE;
	m_topSprite.setScale({scale,scale});
	m_topSprite.setOrigin(32.f, 32.f);
	m_topSprite.setRotation(0);
	m_baseSprite.setScale({ scale,scale });
	m_baseSprite.setOrigin(32.f, 32.f);
	float posX = m_tilePosX * TileMap::TILE_SIZE;
	float posY = m_tilePosY * TileMap::TILE_SIZE;
	m_topSprite.setPosition(posX,posY);
	m_baseSprite.setPosition(posX, posY);
}

void Turret::enableTurret()
{
	enabled = true;
}

void Turret::disableTurret()
{
	enabled = false;
}

void Turret::update(float _deltaTime)
{

	const sf::Vector2f& currentPosition = m_topSprite.getPosition();
	float indexTargetPosX = 0.f;
	float indexTargetPosY = 0.f;
	Thief* thiefTargeted = nullptr;
	Game::get().visit<Thief>([this,&indexTargetPosX, &indexTargetPosY, &thiefTargeted](Thief& _thief) {
		sf::Vector2f spritePos = _thief.getSpritePos();
		indexTargetPosX = spritePos.x;
		indexTargetPosY = spritePos.y;
		thiefTargeted = &_thief;
		return false;
	});
	if (thiefTargeted != nullptr) {
		sf::Vector2f targetPosition{ indexTargetPosX, indexTargetPosY };
		sf::Vector2f direction{ targetPosition - currentPosition };
		direction = math::normalize(direction);
		float angle = math::vectorToAngle(direction);
		m_topSprite.setRotation(90.f + angle);
		timeBeforeNextShoot -= _deltaTime;
		if (timeBeforeNextShoot <= 0.f) {
			shoot(*thiefTargeted);
			timeBeforeNextShoot += cooldown;
		}
	}

	
	
}

void Turret::draw(sf::RenderWindow& _window)
{
	_window.draw(m_baseSprite);
	_window.draw(m_topSprite);
}

void Turret::shoot(Thief& _thiefTargeted)
{
	const sf::Vector2f& currentPosition = m_baseSprite.getPosition();
	Game::get().addGameObject<Missile>(currentPosition.x, currentPosition.y, m_topSprite.getRotation(), &_thiefTargeted);
}
