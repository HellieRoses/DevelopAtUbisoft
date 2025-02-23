#include "GameManager.h"
#include "MathUtils.h"
#include "Game.h"

void GameManager::onPausePressed()
{
	if (m_currentState == GameState::PAUSE) {
		changeState(GameState::GAME);
	}
	else if (m_currentState == GameState::GAME)
	{
		changeState(GameState::PAUSE);
	}
}

void GameManager::changeState(GameState _newState)
{
	if (m_currentState == _newState)
		return;
	//on exit current state
	switch (m_currentState)
	{
	case GameManager::GameState::TITLESCREEN:
		break;
	case GameManager::GameState::PREPARATION:
		initLevel();
		break;
	case GameManager::GameState::GAME:
		break;
	case GameManager::GameState::PAUSE:
		break;
	default:
		break;
	}
	m_currentState = _newState;
	//on enter current state
	switch (m_currentState)
	{
	case GameManager::GameState::TITLESCREEN:

		resetGame();
		break;
	case GameManager::GameState::PREPARATION:
		m_prepText.setString("PREPARATION : Click to enter game");

		break;
	case GameManager::GameState::GAME:
		break;
	case GameManager::GameState::PAUSE:
		m_prepText.setString("PAUSE : Click to enter game");
		break;
	default:
		break;
	}
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
}

void GameManager::draw() {
	m_game->m_window.display();
}

void GameManager::init()
{
	initText();
	m_prepText.setString("TITLE : Click to enter game");
}

void GameManager::drawGame()
{
	m_game->m_tileMap->draw(m_game->m_window);
	drawGameObjects();
	drawUIElements();
}

void GameManager::drawMainText()
{
	m_game->m_window.draw(m_prepText);
}

GameManager::GameManager(Game* _game)
	: m_game(_game)
{
}

void GameManager::update(float _deltaTime) {
	//parcourt liste ennemis + mise à jour
	//delta time 

	m_game->m_window.clear(sf::Color::Black);
	switch (m_currentState)
	{
	case GameManager::GameState::TITLESCREEN:
		drawMainText();
		break;
	case GameManager::GameState::PREPARATION:
		drawMainText();
		break;
	case GameManager::GameState::GAME:
		updateGame(_deltaTime);
		drawGame();
		break;
	case GameManager::GameState::PAUSE:
		drawMainText();
		break;
	default:
		break;
	}

}

void GameManager::updateGame(float _deltaTime)
{
	updateUIElements();

	m_gameObjects.erase(
		std::remove_if(
			m_gameObjects.begin(), m_gameObjects.end(),
			[this](const std::unique_ptr<GameObject>& _go) {
				if (const auto* t = dynamic_cast<Thief*>(_go.get()))
					return isThiefOut(*t);
				return false;
			}),
		m_gameObjects.end()
	);


	if (m_nbCurrentThief <= m_nbThiefsMax && !hasThiefInTile(TileMap::TILE_START_THIEF))
	{
		createThief();
	}


	updateGameObjects(_deltaTime);


	if (playerLoose()) {
		changeState(GameState::TITLESCREEN);
	}
	else if (m_gameObjects.empty() && m_nbCurrentThief > m_nbThiefsMax)
	{
		changeState(GameState::PREPARATION);
	}

}

void GameManager::onMouseClicked(sf::Event _event)
{
	if (_event.mouseButton.button == sf::Mouse::Left)
	{
		switch (m_currentState)
		{
		case GameManager::GameState::TITLESCREEN:
			changeState(GameState::PREPARATION);
			break;
		case GameManager::GameState::PREPARATION:
			changeState(GameState::GAME);
			break;
		case GameManager::GameState::GAME:
		{
			sf::Vector2i localPosition = sf::Mouse::getPosition(m_game->m_window);
			shotThief(localPosition);
		}
		break;
		case GameManager::GameState::PAUSE:
			changeState(GameState::GAME);
			break;
		default:
			break;
		}


	}
}

void GameManager::drawGameObjects()
{
	for (const auto& gameObject : m_gameObjects)
	{
		gameObject->draw(m_game->m_window);
	}

}

void GameManager::updateGameObjects(float _deltaTime)
{

	for (auto& gameObject : m_gameObjects)
	{
		gameObject->update(_deltaTime);
	}
}

void GameManager::drawUIElements()
{
	m_game->m_window.draw(m_playerMoneyText);
	m_game->m_window.draw(m_moneyOutText);
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
	visit<Thief>([this, _mousePos](Thief& _thief) {
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

bool GameManager::playerLoose() const
{
	return m_moneyOut >= 200.f; //TODO
}

void GameManager::createThief()
{
	m_gameObjects.push_back(std::make_unique<Thief>(
		TileMap::TILE_SIZE * 1.5f, TileMap::TILE_START_THIEF.x, TileMap::TILE_START_THIEF.y)
	);
	m_nbCurrentThief++;
}


bool GameManager::hasThiefInTile(TileCoord _tileCoord)
{
	bool result = false;
	visit<Thief>([this, _tileCoord, &result](Thief& _thief) {
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

	m_prepText.setFont(m_game->getFont());
	m_prepText.setFillColor(sf::Color::Blue);
	//m_playerMoneyText.setStyle(sf::Text::Bold);
	m_prepText.setCharacterSize(36);
	m_prepText.setPosition(0, 450);
}
