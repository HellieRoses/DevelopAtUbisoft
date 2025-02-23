#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include <memory>
#include <vector>
#include <functional>
#include "Thief.h"
#include "Player.h"
class Game;
class GameManager
{
	public:
		GameManager(Game* _game);
		void init();
		void update(float _deltaTime);
		void draw();
		void onPausePressed();
		void onMouseClicked(sf::Event _event);
	private:
		Game* m_game;

		enum class GameState {
			TITLESCREEN,
			PREPARATION,
			GAME,
			PAUSE,
		};
		GameState m_currentState{ GameState::TITLESCREEN };
	
		void changeState(GameState _newState);
		void initLevel();
		void resetGame();
		void drawGame();
		void drawMainText();
		void updateGame(float _deltaTime);
		void drawGameObjects();
		void updateGameObjects(float _deltaTime);
		void drawUIElements();
		void updateUIElements();
		bool isThiefOut(const Thief& _thief);
		void shotThief(sf::Vector2i _mousePos);
		bool playerLoose() const;
		template<typename T>
		void visit(std::function<bool(T&)> _visitor) {
			for (const auto& gameObject : m_gameObjects)
			{
				if (Thief* thief = dynamic_cast<Thief*>(gameObject.get()))
					if (!_visitor(*thief))
						break;
			}
		}
		void createThief();
		bool hasThiefInTile(TileCoord _tileCoord);
		std::vector<std::unique_ptr<GameObject>> m_gameObjects;
		uint m_nbThiefsMax = 5;
		uint m_nbCurrentThief = 0;
		Player m_player;
		float m_moneyOut = 0.f;

		sf::Text m_prepText;

		sf::Text m_playerMoneyText;
		void setPlayerMoneyText();

		sf::Text m_moneyOutText;
		void setMoneyOutText();
		void initText();
};

