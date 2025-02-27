#include "PauseManager.h"
#include "Game.h"

PauseManager::PauseManager(Game* _game)
	: m_game(_game)
{
}

void PauseManager::updateState(float _deltaTime)
{
	drawState();
}

void PauseManager::drawState()
{
	m_game->getGameWindow().draw(m_mainText);
}

void PauseManager::onEnterState()
{
	m_mainText.setString("PAUSE : Click to enter game");
}

void PauseManager::onExitState()
{
	return;
}

void PauseManager::initText()
{
	m_mainText.setFont(m_game->getFont());
	m_mainText.setFillColor(sf::Color::Blue);
	m_mainText.setCharacterSize(36);
	m_mainText.setPosition(0, 450);
}
