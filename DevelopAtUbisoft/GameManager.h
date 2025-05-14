#pragma once
#include "GameStateManager.h"
#include "Player.h"
#include "Tile.h"
#include "Vague.h"
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
		void onThiefDead(Thief& _thief);

		void initLevel();
		void resetGame();
		void initText();

		bool playerLoose() const;
		bool hasRoundFinished() const;

		bool isGameFinished() const;

	private:

		uint computeNumberThief() const;

		void drawUIElements();
		void updateUIElements();
		void setPlayerMoneyText();
		void setMoneyOutText();
		void setMainText();

		bool isThiefOut(Thief& _thief);
		void createThief();
		bool hasThiefInTile(TileCoord _tileCoord);

		void enableTurrets();
		void disableTurrets();

		void initUIElements();
		bool playerIsLoosing();

		static std::array<Vague,6> m_vagues;
		
		int m_currentNbVague = -1;
		uint m_currentNbThiefsMax =0;
		uint m_nbCurrentThief =0;
		uint m_nbDeadThief = 0;
		float timeTillNextThief =0.f;

		sf::Sprite m_widePanel;
		sf::Sprite m_playerMoneyPanel;
		sf::Sprite m_moneyOutPanel;
		sf::RectangleShape m_background;

		sf::Text m_titleText;
		sf::Text m_mainText;
		sf::Text m_lastText;

		sf::Text m_playerMoneyText;
		sf::Text m_moneyOutText;

	

		Game* m_game;

};

