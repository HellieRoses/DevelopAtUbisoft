#pragma once
#include "GameStateManager.h"
#include "gameConstants.h"
#include <SFML/Graphics.hpp>
class Game;
class TitleScreenManager :public GameStateManager
{
	public:
		TitleScreenManager(Game* _game);
		void updateState(float _deltaTime);
		void drawState() override;
		void onEnterState() override;
		void onExitState() override;
		void initText();
		void clickOnCredit();
		sf::Sprite& getCreditsButtonSprite() {
			return m_creditsButton;
		}
		sf::Sprite& getPanelSprite() {
			return m_widePanel;
		}
	private:

		void initUIElements();
		void updateUIElements();
		void drawUIElements();

		bool m_inCredit = false;

		sf::Sprite m_widePanel;

		sf::Text m_titleText;
		sf::Text m_titleText2;
		sf::Text m_mainText;
		sf::Text m_lastText;

		sf::Sprite m_creditsButton;
		sf::Text m_creditsButtonText;
		sf::Text m_creditsTitleText;
		sf::Text m_creditsText;
		sf::Sprite m_backgroundImage;
		
		static constexpr float PANEL_POSI_X = BACKGROUND_REAL_SIZE_X / 2 - PANEL_SIZE_X;
		static constexpr float PANEL_POSI_Y = BACKGROUND_REAL_SIZE_Y / 2.5f - PANEL_SIZE_Y;
		static constexpr float CREDIT_POS_X = PANEL_POSI_X + 115;
		static constexpr float CREDIT_BASE_POS_Y = PANEL_POSI_Y + 350;
		static constexpr float CREDIT_OTHER_POS_Y = PANEL_POSI_Y + 400;
		Game* m_game;
		
};

