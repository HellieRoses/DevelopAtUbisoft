#pragma once
#include "GameStateManager.h"
#include "gameConstants.h"
#include <SFML/Graphics.hpp>
class Game;
class PauseManager : public GameStateManager
{
	public:
		PauseManager(Game* _game);
		void updateState(float _deltaTime) override;
		void drawState() override;
		void onEnterState() override;
		void onExitState() override;
		void initText();
		void drawUIElements();
	private:
		void initUIElements();
		void updateUIElements();
		void setPlayerMoneyText();
		void setMoneyOutText();
		sf::Sprite m_widePanel;
		sf::Sprite m_playerMoneyPanel;
		sf::Sprite m_moneyOutPanel;
		sf::RectangleShape m_background;

		sf::Text m_titleText;
		sf::Text m_mainText;
		sf::Text m_lastText;

		sf::Text m_playerMoneyText;
		sf::Text m_moneyOutText;

		static constexpr float PANEL_POSI_X = WINDOW_SIZE_X / 2 - PANEL_SIZE_X / 2;
		static constexpr float PANEL_POSI_Y = WINDOW_SIZE_Y / 2 - PANEL_SIZE_Y / 2;

		Game* m_game;
};

