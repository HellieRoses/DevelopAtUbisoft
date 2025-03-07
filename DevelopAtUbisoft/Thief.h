#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "GameObject.h"
#include "core.h"
#define WALKABLE 1
class Thief:public GameObject
{
	public:
		Thief(const uint _xPosition, const uint _yPosition);
		
		void getShot();
		void getShotByMissile();
		sf::Sprite& getSprite() { return m_sprite; };
		const sf::Sprite& getSprite() const { return m_sprite; };
		sf::Vector2u getTilePos() const { return {m_tilePosY, m_tilePosX}; }
		sf::Vector2f getSpritePos() const { return m_sprite.getPosition(); }

		int getPV() const { return m_pv; }
		bool isDead();
		float getMoneyStolen() const { return m_moneyStolen; };
	private:
		void update(float _deltaTime) override;
		void draw(sf::RenderWindow& _window) override;

		sf::Sprite m_sprite;
		uint m_tilePosX;
		uint m_tilePosY;
		float m_speed;
		int m_pv;
		static constexpr float DEST_EPSILON = 1.f;
		float m_moneyStolen;
};

