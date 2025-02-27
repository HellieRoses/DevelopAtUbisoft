#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "MainManager.h"
#include "core.h"
class Game {
	public:
		Game();
		static Game& get();
		void init(const std::string _windowName);
		void run();
		sf::Texture& getTexture();
		sf::Texture& getThiefTexture();
		sf::Texture& getBaseTurretTexture();
		sf::Texture& getTurret1Texture();
		sf::Font& getFont();
		sf::RenderWindow& getGameWindow();
		TileMap* getTileMap();
		template<typename T>
		void visit(std::function<bool(T&)> _visitor) {
			for (const auto& gameObject : m_gameObjects)
			{
				if (Thief* thief = dynamic_cast<Thief*>(gameObject.get()))
					if (!_visitor(*thief))
						break;
			}
		};
		template<typename T, typename... Args>
		void addGameObject(Args... args) {
			m_gameObjects.push_back(std::make_unique<T>(std::forward<Args>(args)...));
		};
		void clearGameObjects() {
			m_gameObjects.clear();
		}
		void eraseIfGameObjects(std::function<bool(const std::unique_ptr<GameObject>&)> _erasor) {
			m_gameObjects.erase(
				std::remove_if(m_gameObjects.begin(), m_gameObjects.end(), _erasor),
				m_gameObjects.end()
			);
		}

	private:

		

		void update(float _deltaTime);
		void draw();

		void updateGameObjects(float _deltaTime);
		void drawGameObjects();
		std::vector<std::unique_ptr<GameObject>> m_gameObjects;

		sf::RenderWindow m_window;
		std::unique_ptr<TileMap> m_tileMap;

		sf::Texture m_tileMapTexture;
		sf::Texture m_thiefTexture;
		sf::Texture m_baseTurretTexture;
		sf::Texture m_turret1Texture;
		sf::Font m_gameFont;

		MainManager m_mainManager;
};