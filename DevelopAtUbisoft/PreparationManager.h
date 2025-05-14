#pragma once
#include "GameStateManager.h"
#include "gameConstants.h"
#include <SFML/Graphics.hpp>
class Game;
class PreparationManager : public GameStateManager
{
	public:
		PreparationManager(Game* _game);
		void updateState(float _deltaTime) override;
		void drawState() override;
		void onEnterState() override;
		void onExitState() override;
		void initText();
		void onMouseClicked(sf::Vector2i _mousePos);
	private:
		void initUIElements();
		void placeTurret(sf::Vector2i _mousePos);
		void updateUIElements();
		void drawUIElements();
		void setPlayerMoneyText();
		void setMoneyOutText();

		bool playerIsLoosing() const;
		sf::Sprite m_widePanel;
		sf::Sprite m_playerMoneyPanel;
		sf::Sprite m_moneyOutPanel;
		sf::RectangleShape m_background;

		sf::Text m_playerMoneyText;
		sf::Text m_moneyOutText;
		sf::Text m_titleText;
		sf::Text m_mainText;
		sf::Text m_lastText;

		float turret_price = TURRET_PRICE;
		
		Game* m_game;
};

