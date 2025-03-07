#include "Turret.h"
#include "Game.h"
#include "MathUtils.h"
#include "Thief.h"
#include "Missile.h"
#include <iostream>
Turret::Turret(const uint _xPosition, const uint _yPosition)
	: m_tilePosX(_xPosition)
	, m_tilePosY(_yPosition)
{
	m_topSprite = sf::Sprite(Game::get().getTurret1Texture(), sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(MAX_BASE_TILE_SIZE, MAX_BASE_TILE_SIZE)));
	m_baseSprite = sf::Sprite(Game::get().getBaseTurretTexture(), sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(MAX_BASE_TILE_SIZE, MAX_BASE_TILE_SIZE)));
	m_topSprite.setScale({ MAX_SCALE,MAX_SCALE });
	m_topSprite.setOrigin(MAX_ORIGIN, MAX_ORIGIN);
	m_topSprite.setRotation(0);
	m_baseSprite.setScale({ MAX_SCALE,MAX_SCALE });
	m_baseSprite.setOrigin(MAX_ORIGIN, MAX_ORIGIN);
	float posX = m_tilePosX * MINI_TILE_SIZE;
	float posY = m_tilePosY * MINI_TILE_SIZE;
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
