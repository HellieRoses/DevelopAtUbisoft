#include "Missile.h"
#include "Game.h"
#include "MathUtils.h"

Missile::Missile(float _spawnX, float _spawnY, float _angle, Thief* _targetedThief)
	: m_thiefId(_targetedThief->getId())
{
	m_sprite.setTexture(Game::get().getMissileTexture());
	float scale = TileMap::TILE_SIZE / 64.f;
	m_sprite.setScale({ scale,scale });
	m_sprite.setOrigin(32.f, 32.f);
	m_sprite.setPosition({ _spawnX, _spawnY });
	m_sprite.setRotation(_angle);
	m_speed = TileMap::TILE_SIZE * 3.f;
}

void Missile::update(float _deltaTime)
{
	Thief* thief = Game::get().getGameObjectById<Thief>(m_thiefId);
	if (thief != nullptr)
	{
		const sf::Vector2f& currentPosition = m_sprite.getPosition();
		const sf::Vector2f& targetPosition = thief->getSpritePos();

		sf::Vector2f direction{ targetPosition - currentPosition };
		float dist = math::norm(direction);
		direction = math::normalize(direction);
		float angle = math::vectorToAngle(direction);
		m_sprite.setRotation(90.f + angle);
		m_sprite.setPosition(currentPosition + direction * m_speed * _deltaTime);
		if (dist < 1.f) {
			thief->getShotByMissile(); //todo thief wantedestroy in is thief out
			wantDestroy = true;
		}
	}
	else {
		wantDestroy = true;
	}
	
}

void Missile::draw(sf::RenderWindow& _window)
{
	_window.draw(m_sprite);
}
