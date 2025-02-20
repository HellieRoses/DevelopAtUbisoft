#include "Game.h"
#include <SFML/Window.hpp>
#include "MathUtils.h"
#include <iostream>
#include <cstdlib>
Game::Game() 
	: m_window(sf::VideoMode(1600, 900), "")
{
	//m_windowName = _windowName; 
	m_window.setFramerateLimit(60);
}

void Game::init(const std::string _windowName) {
	m_window.setTitle(_windowName);
	if (!m_tileMapTexture.loadFromFile("assets/sprites/tilemap.png")) {
		std::cout << "error on load" << std::endl;
	}
	if (!m_thiefTexture.loadFromFile("assets/sprites/thief.png")) {
		std::cout << "error on load" << std::endl;
	}
	if (!m_gameFont.loadFromFile("assets/fonts/static/SpaceGrotesk-Bold.ttf")) {
		std::cout << "error on load font" << std::endl;
	}
	//tileMap
	initText();
	m_prepText.setString("TITLE : Click to enter game");
}



Game& Game::get() {
	static Game game;
	return game;
}

void Game::run() {
	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}else if (event.type == sf::Event::MouseButtonPressed)
			{
				onMouseClicked(event);
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::P)
				{
					onPausePressed();
				}
			}
			
				
		}
		this->update(1/60.f);
		this->draw();
		
	}
}

sf::Texture& Game::getTexture()
{
	return m_tileMapTexture;
}

sf::Texture& Game::getThiefTexture()
{
	return m_thiefTexture;
}

void Game::onPausePressed()
{
	if (m_currentState == GameState::PAUSE) {
		changeState(GameState::GAME);
	}
	else if (m_currentState == GameState::GAME)
	{
		changeState(GameState::PAUSE);
	}
}

void Game::changeState(GameState _newState)
{
	if (m_currentState == _newState)
		return;
	//on exit current state
	switch (m_currentState)
	{
	case Game::GameState::TITLESCREEN:
		break;
	case Game::GameState::PREPARATION:
		initLevel();
		break;
	case Game::GameState::GAME:
		break;
	case Game::GameState::PAUSE:
		break;
	default:
		break;
	}
	m_currentState = _newState;
	//on enter current state
	switch (m_currentState)
	{
	case Game::GameState::TITLESCREEN:

		resetGame();
		break;
	case Game::GameState::PREPARATION:
		m_prepText.setString("PREPARATION : Click to enter game");
		
		break;
	case Game::GameState::GAME:
		break;
	case Game::GameState::PAUSE:
		m_prepText.setString("PAUSE : Click to enter game");
		break;
	default:
		break;
	}
}

void Game::initLevel()
{
	m_tileMap = std::make_unique<TileMap>();
	m_tileMap->loadTiles();
	m_nbCurrentThief = 0;
	createThief();
}

void Game::resetGame()
{
	m_player.reset();
	m_moneyOut = 0.f;
}

void Game :: draw() {
	m_window.display();
}

void Game::drawGame()
{
	m_tileMap->draw(m_window);
	drawGameObjects();
	drawUIElements();
}

void Game::drawMainText()
{
	m_window.draw(m_prepText);
}

void Game::update(float _deltaTime) {
	//parcourt liste ennemis + mise à jour
	//delta time 

	m_window.clear(sf::Color::Black);
	switch (m_currentState)
	{
	case Game::GameState::TITLESCREEN:
		drawMainText();
		break;
	case Game::GameState::PREPARATION:
		drawMainText();
		break;
	case Game::GameState::GAME:
		updateGame(_deltaTime);
		drawGame();
		break;
	case Game::GameState::PAUSE:
		drawMainText();
		break;
	default:
		break;
	}
	
}

void Game::updateGame(float _deltaTime)
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
		std::cout << "Game over" << std::endl;
		changeState(GameState::TITLESCREEN);
	}else if (m_gameObjects.empty() && m_nbCurrentThief > m_nbThiefsMax)
	{
		changeState(GameState::PREPARATION);
	}

}

void Game::onMouseClicked(sf::Event _event)
{
	if (_event.mouseButton.button == sf::Mouse::Left)
	{
		switch (m_currentState)
		{
		case Game::GameState::TITLESCREEN:
			changeState(GameState::PREPARATION);
			break;
		case Game::GameState::PREPARATION:
			changeState(GameState::GAME);
			break;
		case Game::GameState::GAME:
			{
				sf::Vector2i localPosition = sf::Mouse::getPosition(m_window);
				shotThief(localPosition);
			}
			break;
		case Game::GameState::PAUSE:
			changeState(GameState::GAME);
			break;
		default:
			break;
		}

		
	}
}

void Game::drawGameObjects()
{
	for (const auto& gameObject : m_gameObjects)
	{
		gameObject->draw(m_window);
	}
	
}

void Game::updateGameObjects(float _deltaTime)
{

	for (auto& gameObject : m_gameObjects)
	{
		gameObject->update(_deltaTime);
	}
}

void Game::drawUIElements()
{
	m_window.draw(m_playerMoneyText);
	m_window.draw(m_moneyOutText);
}

void Game::updateUIElements()
{
	setPlayerMoneyText();
	setMoneyOutText();
}

bool Game::isThiefOut(const Thief& _thief)
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

void Game::shotThief(sf::Vector2i _mousePos)
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

bool Game::playerLoose() const
{
	return m_moneyOut >= 200.f; //TODO
}

void Game::createThief()
{
	m_gameObjects.push_back(std::make_unique<Thief>(
		TileMap::TILE_SIZE*1.5f, TileMap::TILE_START_THIEF.x, TileMap::TILE_START_THIEF.y)
	);
	m_nbCurrentThief++;
}


bool Game::hasThiefInTile(TileCoord _tileCoord)
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

void Game::setPlayerMoneyText()
{
	m_playerMoneyText.setString("Money player: " + std::to_string(m_player.getMoney()) + "$");
}

void Game::setMoneyOutText()
{
	m_moneyOutText.setString("Money out :" + std::to_string(m_moneyOut) + "$");
}

void Game::initText()
{
	m_playerMoneyText.setFont(m_gameFont);
	m_playerMoneyText.setFillColor(sf::Color::Blue);
	//m_playerMoneyText.setStyle(sf::Text::Bold);
	m_playerMoneyText.setCharacterSize(14);
	m_playerMoneyText.setPosition(0, 0);
	m_moneyOutText.setFont(m_gameFont);
	m_moneyOutText.setFillColor(sf::Color::Red);
	//m_moneyOutText.setStyle(sf::Text::Bold);
	m_moneyOutText.setCharacterSize(14);
	m_moneyOutText.setPosition(0, 14);

	m_prepText.setFont(m_gameFont);
	m_prepText.setFillColor(sf::Color::Blue);
	//m_playerMoneyText.setStyle(sf::Text::Bold);
	m_prepText.setCharacterSize(36);
	m_prepText.setPosition(0, 450);
}
