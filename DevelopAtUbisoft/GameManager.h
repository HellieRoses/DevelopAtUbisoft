#pragma once
#include "GameStateManager.h"
#include "Player.h"
#include "Tile.h"
#include "Thief.h"
#include <functional>
class Game;
class GameManager :   public GameStateManager
{
public:
		GameManager(Game* _game);
		void updateState(float _deltaTime);
		void drawState();
		void onEnterState();
		void onExitState();

		void shotThief(sf::Vector2i _mousePos);
		void initLevel();
		void resetGame();
		void initText();

		bool playerLoose() const;
		bool hasRoundFinished() const;
	private:
		Game* m_game;

		void drawGameObjects();
		void updateGameObjects(float _deltaTime);
		void drawUIElements();
		void updateUIElements();

		bool isThiefOut(const Thief& _thief);


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
		uint m_nbThiefsMax;
		uint m_nbCurrentThief;

		Player m_player;
		float m_moneyOut;


		sf::Text m_playerMoneyText;
		void setPlayerMoneyText();

		sf::Text m_moneyOutText;
		void setMoneyOutText();

};

