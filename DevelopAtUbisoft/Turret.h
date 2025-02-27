#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "core.h"
class Turret :  public GameObject
{
	public:
		Turret(const uint _xPosition, const uint _yPosition);
	private:
		void update(float _deltaTime) override;
		void draw(sf::RenderWindow& _window) override;
		static constexpr float TEXTURE_SIZE = 64.f;

		sf::Sprite m_topSprite;
		sf::Sprite m_baseSprite;

		uint m_tilePosX;
		uint m_tilePosY;
};

