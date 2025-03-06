#pragma once
#include <SFML/System/Vector2.hpp>
namespace math
{
	float norm(sf::Vector2f _vec);

	sf::Vector2f normalize(sf::Vector2f _vec);

	float vectorToAngle(sf::Vector2f _vec);
	
	constexpr float RAD_TO_DEG = 180 / 3.1415f;
}