#include "Game.h"
#include <SFML/Window.hpp>
#include "MathUtils.h"
#include <iostream>
#include <cstdlib>
Game::Game() 
	: m_window(sf::VideoMode(1280, 720), "")
{
	//m_windowName = _windowName; 
	m_window.setFramerateLimit(60);
}

void Game::init(const std::string _windowName) {
	m_window.setTitle(_windowName);
	if (!m_tileMapTexture.loadFromFile("assets/tilemap.png")) {
		std::cout << "error on load" << std::endl;
	}
	if (!m_thiefTexture.loadFromFile("assets/thief.png")) {
		std::cout << "error on load" << std::endl;
	}
	//tileMap
	m_tileMap = std::make_unique<TileMap>();
	m_tileMap->loadTiles();

	
	createThief();


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

void Game :: draw() {
	m_tileMap->draw(m_window);
	drawGameObjects();
	m_window.display();
}

void Game::update(float _deltaTime) {
	//parcourt liste ennemis + mise à jour
	//delta time 

	visit<Thief>([this](Thief& _thief) {
		isThiefOut(_thief);
		return true;
	});
	if (m_nbCurrentThief <= m_nbThiefsMax && !hasThiefInTile(TileMap::TILE_START_THIEF))
	{
		createThief();
	}
	
	updateGameObjects(_deltaTime);
	if (playerLoose()) {
		std::cout << "Game over" << std::endl;
	}
}

void Game::onMouseClicked(sf::Event _event)
{
	if (_event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i localPosition = sf::Mouse::getPosition(m_window);
		shotThief(localPosition);
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

void Game::isThiefOut(const Thief& _thief)
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
	}
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
	m_gameObjects.push_back(std::make_unique<Thief>(TileMap::TILE_SIZE*1.5, TileMap::TILE_START_THIEF.x, TileMap::TILE_START_THIEF.y));
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