#include "Thief.h"
#include "TileMap.h"
#include "Game.h"
#include <iostream>
#include <sstream>
#include "MathUtils.h"
#include "Animation.h"


Thief::Thief( const uint _xPosition, const uint _yPosition, const float _moneyStolen, const float _speed)
	: m_tilePosX(_xPosition)
	, m_tilePosY(_yPosition)
{
	m_speed = _speed;
	m_pv = 5;
	m_sprite = sf::Sprite(Game::get().getThiefTexture(), sf::IntRect(sf::Vector2i(THIEF_BASE_SPRITE_SIZE *17, 0), sf::Vector2i(THIEF_BASE_SPRITE_SIZE, MAX_BASE_TILE_SIZE)));
	m_sprite.setPosition(m_tilePosX * MINI_TILE_SIZE, m_tilePosY * MINI_TILE_SIZE + THIEF_SPRITE_SIZE/2);
	m_sprite.setOrigin(THIEF_ORIGIN_X, THIEF_ORIGIN_Y);
	m_sprite.setScale({ MAX_SCALE,MAX_SCALE });
	m_moneyStolen = _moneyStolen;
}

Thief::~Thief() = default;

bool Thief::isDead() 
{
	if (m_pv <= 0) {
		wantDestroy = true;
		Game::get().getMainManager().getGameManager().onThiefDead(*this);
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
		if(!m_currentAnimation || m_currentAnimation->getId() != AnimationId::THIEF_LEFT )
			m_currentAnimation = std::make_unique<Animation>(Game::get().getLeftThiefAnimation()); 
	}else if (m_tilePosY > 0 && TileMap::getTileAt(m_tilePosX, m_tilePosY -1) == WALKABLE) {
		indexTargetPosY = m_tilePosY - 1;
		if (!m_currentAnimation || m_currentAnimation->getId() != AnimationId::THIEF_UP)
			m_currentAnimation = std::make_unique<Animation>(Game::get().getUpThiefAnimation());
	}

	if (m_currentAnimation) {
		m_currentAnimation->update(_deltaTime, m_sprite);
	}

	const bool hasArrived = m_tilePosX == indexTargetPosX && m_tilePosY == indexTargetPosY;
	
	if (hasArrived)	{
		return;
	}
	
	sf::Vector2f targetPosition{indexTargetPosX * MINI_TILE_SIZE +MINI_TILE_SIZE/2, indexTargetPosY * MINI_TILE_SIZE + MINI_TILE_SIZE / 2 };
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
	if (Game::get().isDrawDebug()) 
	{
		sf::RectangleShape debugShape;
		debugShape.setOrigin(m_sprite.getOrigin());
		debugShape.setRotation(m_sprite.getRotation());
		debugShape.setPosition(m_sprite.getPosition());
		debugShape.setOutlineColor(sf::Color::Red);
		debugShape.setFillColor(sf::Color::Transparent);
		debugShape.setOutlineThickness(2.0f);
		debugShape.setSize(m_sprite.getLocalBounds().getSize());
		_window.draw(debugShape);
		sf::CircleShape debugPos;
		debugPos.setPosition(m_sprite.getPosition());
		debugPos.setFillColor(sf::Color::Blue);
		debugPos.setRadius(3.f);
		_window.draw(debugPos);


		sf::Text debugTextIndex;
		std::ostringstream stringStream;
		stringStream << m_tilePosX << " " << m_tilePosY; //todo
		debugTextIndex.setString(stringStream.str());
		debugTextIndex.setFont(Game::get().getFont());
		debugTextIndex.setFillColor(sf::Color::Red);
		debugTextIndex.setCharacterSize(15);
		debugTextIndex.setPosition(m_sprite.getPosition() - sf::Vector2f{0,5});
		_window.draw(debugTextIndex);
	}
}

void Thief::getShot()
{
	m_pv -= PV_LOST_ON_SHOT;
	isDead();
}

void Thief::getShotByMissile()
{
	m_pv -= m_pv;
	isDead();
}

