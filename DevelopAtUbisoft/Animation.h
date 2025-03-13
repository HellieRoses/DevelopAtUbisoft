#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "core.h"
class Animation
{
public :
	Animation(float _frameRate, std::vector<sf::IntRect> _frames, sf::Texture* _texture, AnimationId _id);
	void update(float _deltaTime, sf::Sprite& _sprite);
	AnimationId getId() const { return m_id; }

private:
	void nextFrame();

	uint m_currentFrame;
	float m_frameRate;
	float m_timeElapsedCurrentFrame;
	std::vector<sf::IntRect> m_frames;
	sf::Texture* m_texture;
	AnimationId m_id;

};

