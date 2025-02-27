#include "PreparationManager.h"
#include "Game.h"

PreparationManager::PreparationManager(Game* _game)
	: m_game(_game)
{
}

void PreparationManager::updateState(float _deltaTime)
{
	drawState();
}

void PreparationManager::drawState()
{
	m_game->getTileMap()->draw(m_game->getGameWindow());
	m_game->getGameWindow().draw(m_mainText);
}

void PreparationManager::onEnterState()
{
	m_mainText.setString("PREPARATION : Click to enter game");
}

void PreparationManager::onExitState()
{
	return;
}

void PreparationManager::initText()
{
	m_mainText.setFont(m_game->getFont());
	m_mainText.setFillColor(sf::Color::Blue);
	m_mainText.setCharacterSize(36);
	m_mainText.setPosition(0, 450);
}
