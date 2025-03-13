#pragma once
#include "GameStateManager.h"
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
		void placeTurret(sf::Vector2i _mousePos);
		sf::Text m_mainText;

		sf::Text m_playerMoneyText;
		sf::Text m_moneyOutText; //TODO
		Game* m_game;
};

