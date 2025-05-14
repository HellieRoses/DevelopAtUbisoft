#include "Game.h"
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
Game::Game() 
	: m_mainManager(this)
	, m_window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "")
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
	if (!m_tileTexture.loadFromFile(getTexturePath("tileset.png"))) {
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
	if (!m_uiPanel.loadFromFile(getTexturePath("panel_brown_1.png"))) {
		std::cout << "error on load font" << std::endl;
	}
	if (!m_brownMiniPanel.loadFromFile(getTexturePath("buttonLong_brown.png"))) {
		std::cout << "error on load font" << std::endl;
	}
	if (!m_whiteMiniPanel.loadFromFile(getTexturePath("buttonLong_grey.png"))) {
		std::cout << "error on load font" << std::endl;
	}
	if (!m_redMiniPanel.loadFromFile(getTexturePath("buttonLong_red.png"))) {
		std::cout << "error on load font" << std::endl;
	}
	if (!m_blueMiniPanel.loadFromFile(getTexturePath("buttonLong_blue.png"))) {
		std::cout << "error on load font" << std::endl;
	}
	if (!m_background.loadFromFile(getTexturePath("background.png"))) {
		std::cout << "error on load font" << std::endl;
	}

	m_animationThiefLeft = std::make_unique<Animation>(0.2f, std::vector<sf::IntRect>{
		sf::IntRect{ sf::Vector2i(THIEF_BASE_SPRITE_SIZE * 17, 0), sf::Vector2i(THIEF_BASE_SPRITE_SIZE, MAX_BASE_TILE_SIZE) },
		sf::IntRect{ sf::Vector2i(THIEF_BASE_SPRITE_SIZE * 16, 0), sf::Vector2i(THIEF_BASE_SPRITE_SIZE, MAX_BASE_TILE_SIZE) },
		sf::IntRect{ sf::Vector2i(THIEF_BASE_SPRITE_SIZE * 15, 0), sf::Vector2i(THIEF_BASE_SPRITE_SIZE, MAX_BASE_TILE_SIZE) },
		sf::IntRect{ sf::Vector2i(THIEF_BASE_SPRITE_SIZE * 14, 0), sf::Vector2i(THIEF_BASE_SPRITE_SIZE, MAX_BASE_TILE_SIZE) },
		sf::IntRect{ sf::Vector2i(THIEF_BASE_SPRITE_SIZE * 13, 0), sf::Vector2i(THIEF_BASE_SPRITE_SIZE, MAX_BASE_TILE_SIZE) },
		sf::IntRect{ sf::Vector2i(THIEF_BASE_SPRITE_SIZE * 12, 0), sf::Vector2i(THIEF_BASE_SPRITE_SIZE, MAX_BASE_TILE_SIZE) }
		}, 
	&m_thiefTexture,
		AnimationId::THIEF_LEFT);
	m_animationThiefUp = std::make_unique<Animation>(0.2f, std::vector<sf::IntRect>{
		sf::IntRect{ sf::Vector2i(THIEF_BASE_SPRITE_SIZE * 11, 0), sf::Vector2i(THIEF_BASE_SPRITE_SIZE, MAX_BASE_TILE_SIZE) },
			sf::IntRect{ sf::Vector2i(THIEF_BASE_SPRITE_SIZE * 10, 0), sf::Vector2i(THIEF_BASE_SPRITE_SIZE, MAX_BASE_TILE_SIZE) },
			sf::IntRect{ sf::Vector2i(THIEF_BASE_SPRITE_SIZE * 9, 0), sf::Vector2i(THIEF_BASE_SPRITE_SIZE, MAX_BASE_TILE_SIZE) },
			sf::IntRect{ sf::Vector2i(THIEF_BASE_SPRITE_SIZE * 8, 0), sf::Vector2i(THIEF_BASE_SPRITE_SIZE, MAX_BASE_TILE_SIZE) },
			sf::IntRect{ sf::Vector2i(THIEF_BASE_SPRITE_SIZE * 7, 0), sf::Vector2i(THIEF_BASE_SPRITE_SIZE, MAX_BASE_TILE_SIZE) },
			sf::IntRect{ sf::Vector2i(THIEF_BASE_SPRITE_SIZE * 6, 0), sf::Vector2i(THIEF_BASE_SPRITE_SIZE, MAX_BASE_TILE_SIZE) }
	},
		& m_thiefTexture,
		AnimationId::THIEF_UP);

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
				switch (event.key.code)
				{
					case sf::Keyboard::P :
						m_mainManager.onPausePressed();
						break;
					case sf::Keyboard::D :
						m_drawDebug = !m_drawDebug;
						break;
					case sf::Keyboard::M :
						m_player.addMoney(100.0f);
						break;
				}
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				m_mainManager.onMouseMoved(event);
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

sf::Texture& Game::getTileTexture()
{
	return m_tileTexture;
}

sf::Texture& Game::getPanelTexture()
{
	return m_uiPanel;
}

sf::Texture& Game::getBrownPanelTexture()
{
	return m_brownMiniPanel;
}

sf::Texture& Game::getWhitePanelTexture()
{
	return m_whiteMiniPanel;
}

sf::Texture& Game::getRedPanelTexture()
{
	return m_redMiniPanel;
}

sf::Texture& Game::getBluePanelTexture()
{
	return m_blueMiniPanel;
}

sf::Texture& Game::getBackgroundTexture()
{
	return m_background;
}

Animation& Game::getLeftThiefAnimation()
{
	return *m_animationThiefLeft.get();
}

Animation& Game::getUpThiefAnimation()
{
	return *m_animationThiefUp.get();
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
	if (m_mainManager.isPaused()) {
		return;
	}

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