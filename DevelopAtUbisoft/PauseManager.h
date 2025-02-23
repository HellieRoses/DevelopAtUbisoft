#pragma once
#include "GameStateManager.h"
#include <SFML/Graphics.hpp>
class Game;
class PauseManager : public GameStateManager
{
	public:
		PauseManager(Game* _game);
		void updateState(float _deltaTime);
		void drawState();
		void onEnterState();
		void onExitState();
		void initText();
	private:
		sf::Text m_mainText;
		Game* m_game;
};

