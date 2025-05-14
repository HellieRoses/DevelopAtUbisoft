#pragma once
#include "core.h"
class Vague
{
public:
	Vague(uint _nbThief, float _thiefSpeed, float _minSpawn, float _maxSpawn);
	uint getNbThiefMax() {
		return m_nbThiefMax;
	}
	float getThiefSpeed() {
		return m_thiefSpeed;
	}
	float getMinSpawn() {
		return m_minSpawn;
	}
	float getMaxSpawn() {
		return m_maxSpawn;
	}
private:
	uint m_nbThiefMax;
	float m_thiefSpeed;
	float m_minSpawn;
	float m_maxSpawn;
};

