#pragma once
#include "GameStateManager.h"
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
	private:
		sf::Text m_mainText;
		Game* m_game;
		
};

