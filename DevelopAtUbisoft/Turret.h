#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "core.h"
class Thief;
class Turret :  public GameObject
{
	public:
		Turret(const uint _xPosition, const uint _yPosition);
		static constexpr float PRICE = 75.f;
		void enableTurret();
		void disableTurret();
		bool isEnabled() {
			return enabled;
		};
	private:
		void update(float _deltaTime) override;
		void draw(sf::RenderWindow& _window) override;
		void shoot(Thief& _thiefTargeted);
		static constexpr float TEXTURE_SIZE = 64.f;
		sf::Sprite m_topSprite;
		sf::Sprite m_baseSprite;

		uint m_tilePosX;
		uint m_tilePosY;
		bool enabled = false;

		float cooldown = 2.f;
		float timeBeforeNextShoot = 0.f;
};

