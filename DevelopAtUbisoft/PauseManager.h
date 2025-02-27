#pragma once
#include "GameStateManager.h"
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
	private:
		sf::Text m_mainText;
		Game* m_game;
};

