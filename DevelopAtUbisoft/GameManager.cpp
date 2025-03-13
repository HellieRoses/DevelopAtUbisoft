#include "GameManager.h"
#include "TileMap.h"
#include "Turret.h"
#include "Thief.h"
#include "Game.h"
#include "MathUtils.h"
#include <iostream>
GameManager::GameManager(Game* _game)
	: m_game(_game)
{
	m_nbThiefsMax = NB_THIEFS_MAX;
	m_nbCurrentThief = NB_THIEFS_CURRENT;
}

void GameManager::updateState(float _deltaTime)
{
	updateUIElements();
	m_game->visit<Thief>([this](Thief& _thief) {
		isThiefOut(_thief);
		return true;
	});
	

	if (m_nbCurrentThief < m_nbThiefsMax && !hasThiefInTile(TileMap::TILE_START_THIEF))
	{
		createThief();
	}

}

void GameManager::drawState()
{
	m_game->getTileMap()->draw(m_game->getGameWindow());
	drawUIElements();
}

void GameManager::onEnterState()
{
	enableTurrets();
}

void GameManager::onExitState()
{
	disableTurrets();
}

void GameManager::onMouseClicked(sf::Vector2i _mousePos)
{
	shotThief(_mousePos);
}



uint GameManager::computeNumberThief() const
{
	uint nbThief = 0;
	m_game->visit<Thief>([&nbThief](Thief& _thief) {
		nbThief++;
		return true;
		});
	return nbThief;
}

void GameManager::drawUIElements()
{
	m_game->getGameWindow().draw(m_playerMoneyText);
	m_game->getGameWindow().draw(m_moneyOutText);
}


void GameManager::updateUIElements()
{
	setPlayerMoneyText();
	setMoneyOutText();
}

bool GameManager::isThiefOut(Thief& _thief)
{
	
	if (_thief.getTilePos() == TileMap::TILE_END_THIEF)
	{
		float moneyOut = _thief.getMoneyStolen();
		m_game->getPlayer().removeMoney(moneyOut);
		m_game->getPlayer().addMoneyOut(moneyOut);
		_thief.setWantDestroy();
		return true;
	}
	return false;
}

void GameManager::shotThief(sf::Vector2i _mousePos)
{
	m_game->visit<Thief>([this, _mousePos](Thief& _thief) {
		sf::FloatRect rect = _thief.getSprite().getLocalBounds();
		sf::Vector2f spritePos = _thief.getSpritePos();
		sf::Vector2f rectSize = rect.getSize();

		bool isMouseCloseToThiefx = spritePos.x <= _mousePos.x && _mousePos.x <= (spritePos.x + rectSize.x);
		bool isMouseCloseToThiefy = spritePos.y <= _mousePos.y && _mousePos.y <= (spritePos.y + rectSize.y);

		if (isMouseCloseToThiefx && isMouseCloseToThiefy)
		{
			_thief.getShot();
			return false;
		}
		return true;
	});

}

void GameManager::initLevel()
{
	m_nbCurrentThief = 0;
	//createThief();
}

void GameManager::resetGame()
{
	m_game->getPlayer().reset();
	m_game->clearGameObjects();
}

void GameManager::initText()
{
	m_playerMoneyText.setFont(m_game->getFont());
	m_playerMoneyText.setFillColor(sf::Color::Blue);
	//m_playerMoneyText.setStyle(sf::Text::Bold);
	m_playerMoneyText.setCharacterSize(14);
	m_playerMoneyText.setPosition(0, 0);
	m_moneyOutText.setFont(m_game->getFont());
	m_moneyOutText.setFillColor(sf::Color::Red);
	//m_moneyOutText.setStyle(sf::Text::Bold);
	m_moneyOutText.setCharacterSize(14);
	m_moneyOutText.setPosition(0, 14);

}

bool GameManager::playerLoose() const
{
	return m_game->getPlayer().getMoneyOut() >= MONEYOUT_LOOSE;
}

bool GameManager::hasRoundFinished() const
{
	return computeNumberThief() == 0 && m_nbCurrentThief >= m_nbThiefsMax;
}

void GameManager::createThief()
{
	m_game->addGameObject<Thief>(TileMap::TILE_START_THIEF.x, TileMap::TILE_START_THIEF.y);

	m_nbCurrentThief++;
}


bool GameManager::hasThiefInTile(TileCoord _tileCoord)
{
	bool result = false;
	m_game->visit<Thief>([this, _tileCoord, &result](Thief& _thief) {
		sf::Vector2f targetPosition{ _tileCoord.x * MINI_TILE_SIZE,_tileCoord.y * MINI_TILE_SIZE };
		sf::Vector2f thiefPosition = _thief.getSpritePos();
		sf::Vector2f direction{ targetPosition - thiefPosition };
		float dist = math::norm(direction);
		if (dist < MINI_TILE_SIZE)
		{
			result = true;
			return false;
		}
		return true;
	});
	return result;
}

void GameManager::enableTurrets()
{
	m_game->visit<Turret>([](Turret& _turret) {
		_turret.enableTurret();
		return true;
	});
}

void GameManager::disableTurrets()
{
	m_game->visit<Turret>([](Turret& _turret) {
		_turret.disableTurret();
		return true;
	});
}

void GameManager::setPlayerMoneyText()
{
	m_playerMoneyText.setString("Money player: " + std::to_string(m_game->getPlayer().getMoney()) + "$");
}


void GameManager::setMoneyOutText()
{
	m_moneyOutText.setString("Money out :" + std::to_string(m_game->getPlayer().getMoneyOut()) + "$");
}
