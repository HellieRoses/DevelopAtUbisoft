#include "PreparationManager.h"
#include <iostream>
#include "Game.h"
#include "Turret.h"

PreparationManager::PreparationManager(Game* _game)
	: m_game(_game)
{
}

void PreparationManager::updateState(float _deltaTime)
{
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

void PreparationManager::onMouseClicked(sf::Vector2i _mousePos)
{
	placeTurret(_mousePos);
}

void PreparationManager::placeTurret(sf::Vector2i _mousePos)
{
	Player player = m_game->getPlayer();
	if (player.getMoney() >= Turret::PRICE) {
		uint tilePosX = static_cast<int>(std::round(_mousePos.x / (MINI_TILE_SIZE)));
		uint tilePosY = static_cast<int>(std::round(_mousePos.y / (MINI_TILE_SIZE)));
		if(tilePosX < TILE_X_MAX && tilePosY < TILE_Y_MAX){
			if (TileMap::getTileAt(tilePosX, tilePosY) == 0) {
				m_game->addGameObject<Turret>(tilePosX, tilePosY);
				m_game->getPlayer().removeMoney(Turret::PRICE);
			}
		}
	}
	
}
