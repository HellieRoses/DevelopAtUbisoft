#include "PreparationManager.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Game.h"
#include "Turret.h"



PreparationManager::PreparationManager(Game* _game)
	: m_game(_game)
{
	initUIElements();
}

void PreparationManager::updateState(float _deltaTime)
{
	updateUIElements();
}

void PreparationManager::drawState()
{
	m_game->getGameWindow().draw(m_background);
	m_game->getTileMap()->draw(m_game->getGameWindow());
	drawUIElements();
}

void PreparationManager::onEnterState()
{
	setPlayerMoneyText();
	setMoneyOutText();
	if (playerIsLoosing()) {
		m_moneyOutPanel.setTexture(m_game->getRedPanelTexture());
		m_moneyOutText.setFillColor(sf::Color::Red);
	}
}

void PreparationManager::onExitState()
{
	return;
}

void PreparationManager::initText()
{
	std::ostringstream m_titleString;
	m_titleString << "PREPARATION PHASE";

	m_titleText.setString(m_titleString.str());
	m_titleText.setFont(m_game->getFont());
	m_titleText.setFillColor(sf::Color::White);
	m_titleText.setCharacterSize(20);
	m_titleText.setPosition(PANEL_POS_X + 15, PANEL_POS_Y + 20);
	m_titleText.setStyle(sf::Text::Bold);

	std::ostringstream m_mainString;
	m_mainString << "Placing a turret :\n" << "	Cost : " << turret_price <<"$ \n" << "How to place a turret : \n" << "	Right click on any white tile";

	m_mainText.setString(m_mainString.str());
	m_mainText.setFont(m_game->getFont());
	m_mainText.setFillColor(sf::Color::White);
	m_mainText.setCharacterSize(15);
	m_mainText.setPosition(PANEL_POS_X + 15, PANEL_POS_Y + 50);
	m_mainText.setLineSpacing(1.2f);

	std::ostringstream m_lastString;
	m_lastString << "Left click to start the game !";

	m_lastText.setString(m_lastString.str());
	m_lastText.setFont(m_game->getFont());
	m_lastText.setFillColor(sf::Color::Green);
	m_lastText.setCharacterSize(15);
	m_lastText.setPosition(PANEL_POS_X + 18, PANEL_POS_Y + 150);

	m_playerMoneyText.setFont(m_game->getFont());
	m_playerMoneyText.setFillColor(sf::Color::White);
	m_playerMoneyText.setCharacterSize(15);
	m_playerMoneyText.setPosition(MINI_PANEL_POS_X_1 + 15, MINI_PANEL_POS_Y + 45/2 -10);

	m_moneyOutText.setFont(m_game->getFont());
	m_moneyOutText.setFillColor(sf::Color::Black);
	m_moneyOutText.setCharacterSize(15);
	m_moneyOutText.setPosition(MINI_PANEL_POS_X_2 + 30, MINI_PANEL_POS_Y + 45 / 2 - 10);
}

void PreparationManager::onMouseClicked(sf::Vector2i _mousePos)
{
	placeTurret(_mousePos);
}

void PreparationManager::initUIElements()
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

void PreparationManager::placeTurret(sf::Vector2i _mousePos)
{
	
	Player& player = m_game->getPlayer();
	if (player.getMoney() >= turret_price) {
		uint tilePosX = static_cast<int>(std::floor(_mousePos.x / (MINI_TILE_SIZE)));
		uint tilePosY = static_cast<int>(std::floor(_mousePos.y / (MINI_TILE_SIZE)));
		if(tilePosX < TILE_X_MAX && tilePosY < TILE_Y_MAX){
			if (TileMap::getTileAt(tilePosX, tilePosY) == 0) {
				m_game->addGameObject<Turret>(tilePosX, tilePosY);
				player.removeMoney(turret_price);
				turret_price += 50.f;
			}
		}
	}
	
}

void PreparationManager::updateUIElements()
{
	setPlayerMoneyText();
	setMoneyOutText();
	std::ostringstream m_mainString;
	m_mainString << "Placing a turret :\n" << "	Cost : " << turret_price << "$ \n" << "How to place a turret : \n" << "	Right click on any white tile";

	m_mainText.setString(m_mainString.str());
}

void PreparationManager::drawUIElements()
{
	m_game->getGameWindow().draw(m_widePanel);
	m_game->getGameWindow().draw(m_playerMoneyPanel);
	m_game->getGameWindow().draw(m_moneyOutPanel);
	m_game->getGameWindow().draw(m_playerMoneyText);
	m_game->getGameWindow().draw(m_moneyOutText);
	m_game->getGameWindow().draw(m_titleText);
	m_game->getGameWindow().draw(m_mainText);
	m_game->getGameWindow().draw(m_lastText);
}

void PreparationManager::setPlayerMoneyText()
{
	std::ostringstream stringStream;
	stringStream << "Money player : " << std::fixed << std::setprecision(2) << m_game->getPlayer().getMoney() << "$";
	m_playerMoneyText.setString(stringStream.str());
}

bool PreparationManager::playerIsLoosing() const
{
	return m_game->getPlayer().getMoneyOut() <= MONEYOUT_LOOSE && m_game->getPlayer().getMoneyOut() > (MONEYOUT_LOOSE - 30.f);
}

void PreparationManager::setMoneyOutText()
{
	std::ostringstream stringStream;
	stringStream << "Money out : " << std::fixed << std::setprecision(2) << m_game->getPlayer().getMoneyOut() << "$";

	m_moneyOutText.setString(stringStream.str());
}
