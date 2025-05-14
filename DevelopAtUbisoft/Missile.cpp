#include "Missile.h"
#include "Game.h"
#include "MathUtils.h"
#include "gameConstants.h"

Missile::Missile(float _spawnX, float _spawnY, float _angle, Thief* _targetedThief)
	: m_thiefId(_targetedThief->getId())
{
	m_sprite.setTexture(Game::get().getMissileTexture());
	m_sprite.setScale({ MAX_SCALE,MAX_SCALE });
	m_sprite.setOrigin(MAX_ORIGIN, MAX_ORIGIN);
	m_sprite.setPosition({ _spawnX, _spawnY });
	m_sprite.setRotation(_angle);
	m_speed = _targetedThief->getSpeed()*1.5f;
}

void Missile::update(float _deltaTime)
{
	Thief* thief = Game::get().getGameObjectById<Thief>(m_thiefId);
	if (thief != nullptr)
	{
		directAndShoot(_deltaTime, thief);
	}
	else {
		wantDestroy = true;
	}
}

void Missile::draw(sf::RenderWindow& _window)
{
	_window.draw(m_sprite);
}

void Missile::directAndShoot(float _deltaTime, Thief* thief)
{
	const sf::Vector2f& currentPosition = m_sprite.getPosition();
	const sf::Vector2f& targetPosition = thief->getSpritePos();

	sf::Vector2f direction{ targetPosition - currentPosition };
	float dist = math::norm(direction);
	direction = math::normalize(direction);
	float angle = math::vectorToAngle(direction);
	float distFrame = std::min( m_speed * _deltaTime, dist);
	m_sprite.setRotation(90.f + angle);
	m_sprite.setPosition(currentPosition + direction * distFrame);
	if (dist < m_sprite.getLocalBounds().getSize().x * 0.25f ) {
		thief->getShotByMissile();
		wantDestroy = true;
	}
}
