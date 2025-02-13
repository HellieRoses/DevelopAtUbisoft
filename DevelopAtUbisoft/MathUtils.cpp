#include "MathUtils.h"
#include  <math.h> 
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
}
