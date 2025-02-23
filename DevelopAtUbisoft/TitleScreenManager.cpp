#include "TitleScreenManager.h"
#include "Game.h"
TitleScreenManager::TitleScreenManager(Game* _game)
	: m_game(_game)
{
}

void TitleScreenManager::updateState(float _deltaTime)
{
	drawState();
}

void TitleScreenManager::drawState()
{
	m_game->m_window.draw(m_mainText);
}

void TitleScreenManager::onEnterState()
{
	//TODO : resetGame
	return;
}

void TitleScreenManager::onExitState()
{
	return;
}

void TitleScreenManager::initText()
{
	m_mainText.setFont(m_game->getFont());
	m_mainText.setFillColor(sf::Color::Blue);
	m_mainText.setCharacterSize(36);
	m_mainText.setPosition(0, 450);
	m_mainText.setString("TITLE : Click to enter game");
}
