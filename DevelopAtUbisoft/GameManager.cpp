#include "GameManager.h"

#include <iostream>
#include <sstream>
#include <iomanip>

#include "Game.h"
#include "MathUtils.h"
#include "TileMap.h"
#include "Turret.h"
#include "Thief.h"

std::array<Vague, 6> GameManager::m_vagues = {
	Vague(6, MINI_TILE_SIZE * 1.5f, 0.5f, 1.5f),
	Vague(11, MINI_TILE_SIZE * 1.8f, 0.2f, 1.f),
	Vague(17, MINI_TILE_SIZE * 2.5f, 0.1f, 0.8f),
	Vague(25, MINI_TILE_SIZE * 3.f, 0.1,0.5f),
	Vague(35, MINI_TILE_SIZE * 5.f, 0.05f,0.2f),
	Vague(50, MINI_TILE_SIZE * 5.f, 0.05f,0.2f)
};

GameManager::GameManager(Game* _game)
	: m_game(_game)
{
	m_nbCurrentThief = NB_THIEFS_CURRENT;
	initUIElements();
}

void GameManager::updateState(float _deltaTime)
{
	updateUIElements();
	m_game->visit<Thief>([this](Thief& _thief) {
		isThiefOut(_thief);
		return true;
	});
	

	if (m_nbCurrentThief < m_currentNbThiefsMax && !hasThiefInTile(TileMap::TILE_START_THIEF))
	{
		if(timeTillNextThief <= 0.f)
			createThief();
		timeTillNextThief -= _deltaTime;
	}

}

void GameManager::drawState()
{
	m_game->getGameWindow().draw(m_background);
	m_game->getTileMap()->draw(m_game->getGameWindow());
	drawUIElements();

	if (m_game->isDrawDebug()) {
		sf::Text debugTextIndex;
		std::ostringstream stringStream;
		stringStream << "wave: " << m_currentNbVague << ", dead thief: " << m_nbDeadThief << "/" << m_currentNbThiefsMax;
		debugTextIndex.setString(stringStream.str());
		debugTextIndex.setFont(Game::get().getFont());
		debugTextIndex.setFillColor(sf::Color::Black);
		debugTextIndex.setOutlineColor(sf::Color::White);
		debugTextIndex.setOutlineThickness(10.f);
		debugTextIndex.setCharacterSize(15);
		debugTextIndex.setPosition({0,0 });
		m_game->getGameWindow().draw(debugTextIndex);
	}
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

	m_game->getGameWindow().draw(m_widePanel);
	m_game->getGameWindow().draw(m_playerMoneyPanel);
	m_game->getGameWindow().draw(m_moneyOutPanel);
	m_game->getGameWindow().draw(m_playerMoneyText);
	m_game->getGameWindow().draw(m_moneyOutText);;
	m_game->getGameWindow().draw(m_titleText);
	m_game->getGameWindow().draw(m_mainText);
	m_game->getGameWindow().draw(m_lastText);
}


void GameManager::updateUIElements()
{
	setPlayerMoneyText();
	setMoneyOutText();
	setMainText();
	if (playerIsLoosing()) {
		m_moneyOutPanel.setTexture(m_game->getRedPanelTexture());
		m_moneyOutText.setFillColor(sf::Color::Red);
	}
}

bool GameManager::isThiefOut(Thief& _thief)
{
	
	if (_thief.getTilePos() == TileMap::TILE_END_THIEF)
	{
		float moneyOut = _thief.getMoneyStolen();
		m_game->getPlayer().removeMoney(moneyOut);
		m_game->getPlayer().addMoneyOut(moneyOut);
		_thief.setWantDestroy();
		m_nbDeadThief++;
		return true;
	}
	return false;
}

void GameManager::shotThief(sf::Vector2i _mousePos)
{
	m_game->visit<Thief>([this, _mousePos](Thief& _thief) {
		sf::FloatRect rect = _thief.getSprite().getLocalBounds();
		sf::Vector2f spritePos = _thief.getSpritePos() - _thief.getSprite().getOrigin();
		sf::Vector2f rectSize = rect.getSize();
		bool isMouseCloseToThiefx = spritePos.x <= _mousePos.x && _mousePos.x <= (spritePos.x + rectSize.x);
		bool isMouseCloseToThiefy = spritePos.y <= _mousePos.y && _mousePos.y <= (spritePos.y + rectSize.y);
		//FIX
		if (isMouseCloseToThiefx && isMouseCloseToThiefy)
		{
			_thief.getShot();
			return false;
		}
		return true;
	});

}

void GameManager::onThiefDead(Thief& _thief)
{
	m_game->getPlayer().addMoney(_thief.getMoneyStolen());
	m_nbDeadThief++;
}

void GameManager::initLevel()
{
	m_nbCurrentThief = 0;
	m_currentNbVague++; //TODO check
	m_currentNbThiefsMax = m_vagues[m_currentNbVague].getNbThiefMax();
	m_nbDeadThief = 0;
}

//todo money player can be lower than 0 volà quoi
void GameManager::resetGame()
{
	m_game->getPlayer().reset();
	m_game->clearGameObjects();
	m_currentNbVague = 0;
	m_currentNbThiefsMax = m_vagues[m_currentNbVague].getNbThiefMax();
}

void GameManager::initText()
{
	std::ostringstream m_titleString;
	m_titleString << "GAME PHASE";

	m_titleText.setString(m_titleString.str());
	m_titleText.setFont(m_game->getFont());
	m_titleText.setFillColor(sf::Color::White);
	m_titleText.setCharacterSize(20);
	m_titleText.setPosition(PANEL_POS_X + 15, PANEL_POS_Y + 20);
	m_titleText.setStyle(sf::Text::Bold);


	m_mainText.setFont(m_game->getFont());
	m_mainText.setFillColor(sf::Color::White);
	m_mainText.setCharacterSize(15);
	m_mainText.setPosition(PANEL_POS_X + 15, PANEL_POS_Y + 50);
	m_mainText.setLineSpacing(1.2f);

	std::ostringstream m_lastString;
	m_lastString << "Press P to pause the game";

	m_lastText.setString(m_lastString.str());
	m_lastText.setFont(m_game->getFont());
	m_lastText.setFillColor(sf::Color::Green);
	m_lastText.setCharacterSize(15);
	m_lastText.setPosition(PANEL_POS_X + 18, PANEL_POS_Y + 150);

	m_playerMoneyText.setFont(m_game->getFont());
	m_playerMoneyText.setFillColor(sf::Color::White);
	m_playerMoneyText.setCharacterSize(15);
	m_playerMoneyText.setPosition(MINI_PANEL_POS_X_1 + 15, MINI_PANEL_POS_Y + 45 / 2 - 10);
	
	m_moneyOutText.setFont(m_game->getFont());
	m_moneyOutText.setFillColor(sf::Color::Black);
	m_moneyOutText.setCharacterSize(15);
	m_moneyOutText.setPosition(MINI_PANEL_POS_X_2 + 30, MINI_PANEL_POS_Y + 45 / 2 - 10);

}

bool GameManager::playerLoose() const
{
	return m_game->getPlayer().getMoneyOut() >= MONEYOUT_LOOSE || m_game->getPlayer().getMoney() < 0.f;
}

bool GameManager::hasRoundFinished() const
{
	return m_nbDeadThief == m_currentNbThiefsMax;
}

bool GameManager::isGameFinished() const
{
	return m_currentNbVague == m_vagues.size();
}

void GameManager::createThief()
{
	Vague currentVague = m_vagues[m_currentNbVague];

	m_game->addGameObject<Thief>(TileMap::TILE_START_THIEF.x, TileMap::TILE_START_THIEF.y, MONEY_STOLEN, currentVague.getThiefSpeed());

	m_nbCurrentThief++;
	timeTillNextThief = math::randomFloat(currentVague.getMinSpawn(), currentVague.getMaxSpawn());
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

void GameManager::initUIElements()
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

bool GameManager::playerIsLoosing()
{
	return m_game->getPlayer().getMoneyOut() <= MONEYOUT_LOOSE && m_game->getPlayer().getMoneyOut() > (MONEYOUT_LOOSE - 30.f);
}

void GameManager::setPlayerMoneyText()
{
	std::ostringstream stringStream;
	stringStream <<"Money player : " <<  std::fixed << std::setprecision(2) << m_game->getPlayer().getMoney() << "$";
	m_playerMoneyText.setString( stringStream.str() );
}


void GameManager::setMoneyOutText()
{
	std::ostringstream stringStream;
	stringStream << "Money out : " << std::fixed << std::setprecision(2) << m_game->getPlayer().getMoneyOut() << "$";

	m_moneyOutText.setString(stringStream.str());
}

void GameManager::setMainText()
{
	std::ostringstream m_mainString;
	m_mainString << "Current Wave : " << (m_currentNbVague+1) << "\n" << "How to kill a Thief : \n" << "	Left click on thief \n";

	m_mainText.setString(m_mainString.str());
}
