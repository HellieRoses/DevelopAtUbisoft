#include "Animation.h"

Animation::Animation(float _frameRate, std::vector<sf::IntRect> _frames, sf::Texture* _texture, AnimationId _id)
	: m_frameRate(_frameRate)
	, m_frames(_frames)
	, m_texture(_texture)
	, m_currentFrame(0)
	, m_timeElapsedCurrentFrame(0.f)
	, m_id(_id)
{
}

void Animation::update(float _deltaTime, sf::Sprite& _sprite)
{
	m_timeElapsedCurrentFrame += _deltaTime;
	while(m_timeElapsedCurrentFrame >= m_frameRate) {
		nextFrame();
		m_timeElapsedCurrentFrame -= m_frameRate;
	}
	_sprite.setTextureRect(m_frames.at(m_currentFrame));
}


void Animation::nextFrame()
{
	m_currentFrame++;
	if (m_currentFrame >= m_frames.size()) {
		m_currentFrame = 0;
	}

}
