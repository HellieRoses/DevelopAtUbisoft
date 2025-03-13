#pragma once
#include "GameStateManager.h"
#include "Player.h"
#include "Tile.h"
#include <functional>
class Game;
class Thief;
class GameManager :   public GameStateManager
{
public:
		GameManager(Game* _game);
		void updateState(float _deltaTime) override;
		void drawState() override;
		void onEnterState() override;
		void onExitState() override;
		void onMouseClicked(sf::Vector2i _mousePos);

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
		void setPlayerMoneyText();
		void setMoneyOutText();

		bool isThiefOut(Thief& _thief);
		void createThief();
		bool hasThiefInTile(TileCoord _tileCoord);

		void enableTurrets();
		void disableTurrets();

		
		uint m_nbThiefsMax;
		uint m_nbCurrentThief;

		

		sf::Text m_playerMoneyText;
		sf::Text m_moneyOutText;

		Game* m_game;

};

