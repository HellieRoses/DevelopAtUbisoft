#include "MathUtils.h"
#include  <math.h> 
#include <iostream>
namespace math
{
	float norm(sf::Vector2f _vec)
	{
		return sqrt(_vec.x * _vec.x + _vec.y * _vec.y);
	}

	sf::Vector2f normalize(sf::Vector2f _vec)
	{
		const float normVec = norm(_vec);
		if (normVec == 0.f)
			return {};
		return _vec / normVec;
	}

	float vectorToAngle(sf::Vector2f _vec)
	{
		float angle = atan2(_vec.y, _vec.x);
		float degree = angle * math::RAD_TO_DEG;
		return degree;
	}
	float randomFloat(float min, float max)
	{
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = max - min;
		float r = random * diff;
		return min + r;
	}
}
