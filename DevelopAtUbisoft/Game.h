#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "GameManager.h"
#include "core.h"
class Game {
	public:
		Game();
		static Game& get();
		void init(const std::string _windowName);
		void run();
		sf::Texture& getTexture();
		sf::Texture& getThiefTexture();
		sf::Font& getFont();

		sf::RenderWindow m_window;
		std::unique_ptr<TileMap> m_tileMap;
	private:
	
		sf::Texture m_tileMapTexture;
		sf::Texture m_thiefTexture;
		sf::Font m_gameFont;

		void update(float _deltaTime);
		void draw();

		GameManager m_gameManager;
};