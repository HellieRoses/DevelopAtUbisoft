#include "PauseManager.h"
#include "Game.h"
#include <sstream>
#include <iomanip>

PauseManager::PauseManager(Game* _game)
	: m_game(_game)
{
	initUIElements();
}

void PauseManager::updateState(float _deltaTime)
{
	updateUIElements();
}

void PauseManager::drawState()
{
	m_game->getGameWindow().draw(m_background);
	m_game->getTileMap()->draw(m_game->getGameWindow());
	drawUIElements();
}

void PauseManager::onEnterState()
{
	m_mainText.setString("PAUSE : Click to enter game");
}

void PauseManager::onExitState()
{
	return;
}

void PauseManager::initUIElements()
{
	m_background = sf::RectangleShape({ BACKGROUND_REAL_SIZE_X ,BACKGROUND_REAL_SIZE_Y });
	sf::Color color(108, 137, 136);
	m_background.setFillColor(color);

	m_widePanel = sf::Sprite(m_game->getPanelTexture(), sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(PANEL_SIZE_X, PANEL_SIZE_Y)));
	m_widePanel.setPosition({ PANEL_POS_X,PANEL_POS_Y });

	m_playerMoneyPanel = sf::Sprite(m_game->getBrownPanelTexture(), sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(MINI_PANEL_SIZE_X, MINI_PANEL_SIZE_Y)));
	m_playerMoneyPanel.setPosition({ MINI_PANEL_POS_X_1 , MINI_PANEL_POS_Y });
	m_playerMoneyPanel.setScale(MINI_PANEL_SCALE_X, MINI_PANEL_SCALE_Y);

	m_moneyOutPanel = sf::Sprite(m_game->getWhitePanelTexture(), sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(MINI_PANEL_SIZE_X, MINI_PANEL_SIZE_Y)));
	m_moneyOutPanel.setPosition({ MINI_PANEL_POS_X_2 , MINI_PANEL_POS_Y });
	m_moneyOutPanel.setScale(MINI_PANEL_SCALE_X, MINI_PANEL_SCALE_Y);
}

void PauseManager::initText()
{
	std::ostringstream m_titleString;
	m_titleString << "PAUSE PHASE";

	m_titleText.setString(m_titleString.str());
	m_titleText.setFont(m_game->getFont());
	m_titleText.setFillColor(sf::Color::White);
	m_titleText.setCharacterSize(20);
	m_titleText.setPosition(PANEL_POS_X + 50, PANEL_POS_Y + 20);
	m_titleText.setStyle(sf::Text::Bold);



	std::ostringstream m_lastString;
	m_lastString << "To enter the Game : \n" << "	Press P or Click";

	m_lastText.setString(m_lastString.str());
	m_lastText.setFont(m_game->getFont());
	m_lastText.setFillColor(sf::Color::Green);
	m_lastText.setCharacterSize(15);
	m_lastText.setPosition(PANEL_POS_X + 50, PANEL_POS_Y + 140);

	m_playerMoneyText.setFont(m_game->getFont());
	m_playerMoneyText.setFillColor(sf::Color::White);
	m_playerMoneyText.setCharacterSize(15);
	m_playerMoneyText.setPosition(MINI_PANEL_POS_X_1 + 15, MINI_PANEL_POS_Y + 45 / 2 - 10);

	m_moneyOutText.setFont(m_game->getFont());
	m_moneyOutText.setFillColor(sf::Color::Black);
	m_moneyOutText.setCharacterSize(15);
	m_moneyOutText.setPosition(MINI_PANEL_POS_X_2 + 30, MINI_PANEL_POS_Y + 45 / 2 - 10);

}

void PauseManager::updateUIElements()
{
	m_game->getGameWindow().draw(m_widePanel);
	m_game->getGameWindow().draw(m_playerMoneyPanel);
	m_game->getGameWindow().draw(m_moneyOutPanel);
	m_game->getGameWindow().draw(m_playerMoneyText);
	m_game->getGameWindow().draw(m_moneyOutText);;
	m_game->getGameWindow().draw(m_titleText);
	m_game->getGameWindow().draw(m_mainText);
	m_game->getGameWindow().draw(m_lastText);
}

void PauseManager::drawUIElements()
{
	setPlayerMoneyText();
	setMoneyOutText();
}

void PauseManager::setPlayerMoneyText()
{
	std::ostringstream stringStream;
	stringStream << "Money player : " << std::fixed << std::setprecision(2) << m_game->getPlayer().getMoney() << "$";
	m_playerMoneyText.setString(stringStream.str());
}

void PauseManager::setMoneyOutText()
{
	std::ostringstream stringStream;
	stringStream << "Money out : " << std::fixed << std::setprecision(2) << m_game->getPlayer().getMoneyOut() << "$";

	m_moneyOutText.setString(stringStream.str());
}
