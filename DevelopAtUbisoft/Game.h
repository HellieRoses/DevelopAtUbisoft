#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include <memory>
#include <vector>
#include <functional>
#include "Thief.h"
#include "Player.h"
#include "core.h"
class Game {
	public:
		Game();
		static Game& get();
		void init(const std::string _windowName);
		void run();
		sf::Texture& getTexture();
		sf::Texture& getThiefTexture();
	private:
		void draw();
		void update(float _deltaTime);
		void onMouseClicked(sf::Event _event);
		void drawGameObjects();
		void updateGameObjects(float _deltaTime);
		void drawUIElements();
		void updateUIElements();
		bool isThiefOut(const Thief& _thief);
		void shotThief(sf::Vector2i _mousePos);
		bool playerLoose() const;
		template<typename T>
		void visit(std::function<bool(T&)> _visitor){
			for (const auto& gameObject : m_gameObjects)
			{
				if (Thief* thief = dynamic_cast<Thief*>(gameObject.get()))
					if (!_visitor(*thief))
						break;
			}
		}
		void createThief();
		bool hasThiefInTile(TileCoord _tileCoord);
		sf::RenderWindow m_window;
		std::unique_ptr<TileMap> m_tileMap;
		sf::Texture m_tileMapTexture;
		sf::Texture m_thiefTexture;
		std::vector<std::unique_ptr<GameObject>> m_gameObjects;
		uint m_nbThiefsMax = 10;
		uint m_nbCurrentThief = 0;
		Player m_player;
		float m_moneyOut = 0.f;

		sf::Font m_gameFont;

		sf::Text m_playerMoneyText;
		void setPlayerMoneyText();

		sf::Text m_moneyOutText;
		void setMoneyOutText();
		void initText();

};