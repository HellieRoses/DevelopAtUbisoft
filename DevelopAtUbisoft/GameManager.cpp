#include "GameManager.h"
#include "TileMap.h"
#include "Game.h"
#include "MathUtils.h"
GameManager::GameManager(Game* _game)
	: m_game(_game)
	, m_player()
{
	m_nbThiefsMax = 10;
	m_nbCurrentThief = 0;
	m_moneyOut = 0.f;
}

void GameManager::updateState(float _deltaTime)
{
	updateUIElements();
	m_game->eraseIfGameObjects([this](const std::unique_ptr<GameObject>& _go) {
		if (const auto* t = dynamic_cast<Thief*>(_go.get()))
			return isThiefOut(*t);
		return false;
		});

	if (m_nbCurrentThief <= m_nbThiefsMax && !hasThiefInTile(TileMap::TILE_START_THIEF))
	{
		createThief();
	}



	drawState();
}

void GameManager::drawState()
{
	m_game->getTileMap()->draw(m_game->getGameWindow());
	drawUIElements();
}

void GameManager::onEnterState()
{
}

void GameManager::onExitState()
{
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

bool GameManager::isThiefOut(const Thief& _thief)
{
	if (_thief.isDead() || _thief.getTilePos() == TileMap::TILE_END_THIEF)
	{
		float moneyOut = _thief.getMoneyStolen();
		if (!_thief.isDead())
		{
			m_player.removeMoney(moneyOut);
			m_moneyOut += moneyOut;
		}
		else
		{
			m_player.addMoney(moneyOut);
		}
		return true;
	}
	return false;
}

void GameManager::shotThief(sf::Vector2i _mousePos)
{
	m_game->visit<Thief>([this, _mousePos](Thief& _thief) {
		sf::FloatRect rect = _thief.getSprite().getLocalBounds();
		sf::Vector2f spritePos = _thief.getSpritePos();
		sf::Vector2f rectSize = rect.getSize() * TileMap::TILE_SCALE;

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
	createThief();
}

void GameManager::resetGame()
{
	m_player.reset();
	m_moneyOut = 0.f;
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
	return m_moneyOut >= 100.f;
}

bool GameManager::hasRoundFinished() const
{
	return computeNumberThief() == 0 && m_nbCurrentThief > m_nbThiefsMax;
}

void GameManager::createThief()
{
	m_game->addGameObject<Thief>(TileMap::TILE_SIZE * 1.5f, TileMap::TILE_START_THIEF.x, TileMap::TILE_START_THIEF.y);

	m_nbCurrentThief++;
}


bool GameManager::hasThiefInTile(TileCoord _tileCoord)
{
	bool result = false;
	m_game->visit<Thief>([this, _tileCoord, &result](Thief& _thief) {
		sf::Vector2f targetPosition{ _tileCoord.x * TileMap::TILE_SIZE,_tileCoord.y * TileMap::TILE_SIZE };
		sf::Vector2f thiefPosition = _thief.getSpritePos();
		sf::Vector2f direction{ targetPosition - thiefPosition };
		float dist = math::norm(direction);
		if (dist < TileMap::TILE_SIZE)
		{
			result = true;
			return false;
		}
		return true;
	});
	return result;
}

void GameManager::setPlayerMoneyText()
{
	m_playerMoneyText.setString("Money player: " + std::to_string(m_player.getMoney()) + "$");
}


void GameManager::setMoneyOutText()
{
	m_moneyOutText.setString("Money out :" + std::to_string(m_moneyOut) + "$");
}
