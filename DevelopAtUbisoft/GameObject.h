#pragma once
#include <SFML/Graphics.hpp>
class GameObject
{
	public:
		virtual void update(float _deltaTime) =0;
		virtual void draw(sf::RenderWindow& _window) = 0;
};

