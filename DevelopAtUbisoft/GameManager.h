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

		uint computeNumberThief() const;

		void drawUIElements();
		void updateUIElements();

		bool isThiefOut(const Thief& _thief);
		void createThief();
		bool hasThiefInTile(TileCoord _tileCoord);
		void setPlayerMoneyText();
		void setMoneyOutText();

		
		uint m_nbThiefsMax;
		uint m_nbCurrentThief;

		Player m_player;
		float m_moneyOut;

		sf::Text m_playerMoneyText;
		sf::Text m_moneyOutText;

		Game* m_game;

};

