#pragma once
#include "GameObject.h"
#include "Thief.h"
class Missile: public GameObject
{
public:
	Missile(float _spawnX,float _spawnY,float _angle,Thief* _targetedThief);
private:
	void update(float _deltaTime) override;
	void draw(sf::RenderWindow& _window) override;
	int m_thiefId;
	sf::Sprite m_sprite;
	float m_speed;
};

