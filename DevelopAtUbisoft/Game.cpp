#include "Game.h"
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
Game::Game() 
	: m_mainManager(this)
	, m_window(sf::VideoMode(1600, 900), "")
	, m_player()
{
	//m_windowName = _windowName; 
	m_window.setFramerateLimit(60);
}

void Game::init(const std::string _windowName) {
	m_window.setTitle(_windowName);
	if (!m_tileMapTexture.loadFromFile(getTexturePath("tilemap.png"))) {
		std::cout << "error on load" << std::endl;
	}
	if (!m_thiefTexture.loadFromFile(getTexturePath("thief.png"))) {
		std::cout << "error on load" << std::endl;
	}
	if (!m_baseTurretTexture.loadFromFile(getTexturePath("base_turret.png"))) {
		std::cout << "error on load" << std::endl;
	}
	if (!m_turret1Texture.loadFromFile(getTexturePath("turret_1.png"))) {
		std::cout << "error on load" << std::endl;
	}
	if (!m_missileTexture.loadFromFile(getTexturePath("missile.png"))) {
		std::cout << "error on load font" << std::endl;
	}
	if (!m_gameFont.loadFromFile("assets/fonts/static/SpaceGrotesk-Bold.ttf")) {
		std::cout << "error on load font" << std::endl;
	}

	//tileMap
	m_mainManager.init();
	m_tileMap = std::make_unique<TileMap>();
	m_tileMap->loadTiles();
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
				m_mainManager.onMouseClicked(event);
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::P)
				{
					m_mainManager.onPausePressed();
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

sf::Texture& Game::getBaseTurretTexture()
{
	return m_baseTurretTexture;
}

sf::Texture& Game::getTurret1Texture()
{
	return m_turret1Texture;
}

sf::Texture& Game::getMissileTexture()
{
	return m_missileTexture;
}

sf::Font& Game::getFont()
{
	return m_gameFont;
}

sf::RenderWindow& Game::getGameWindow()
{
	return m_window;
}

TileMap* Game::getTileMap()
{
	return m_tileMap.get();
}

std::string Game::getTexturePath(const std::string _fileName)
{
	return SPRITES_PATH + _fileName;
}

void Game::update(float _deltaTime)
{
	m_mainManager.update(_deltaTime);
	updateGameObjects(_deltaTime);
}

void Game::draw()
{
	drawGameObjects();
	m_mainManager.draw();
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
	if (!m_gameObjectsToAdd.empty())
	{
		m_gameObjects.insert(
			m_gameObjects.end(),
			std::make_move_iterator( m_gameObjectsToAdd.begin()), 
			std::make_move_iterator(m_gameObjectsToAdd.end())
		);
		m_gameObjectsToAdd.clear();
	}

	for (auto& gameObject : m_gameObjects)
	{
		gameObject->update(_deltaTime);
	}

	eraseIfGameObjects([](const std::unique_ptr<GameObject>& _go) {
		return _go->wantDestroy;
	});
}