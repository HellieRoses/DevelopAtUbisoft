#pragma once
#include <string>
#include <memory>
#include "GameStateManager.h"
#include "TitleScreenManager.h"
#include "PreparationManager.h"
#include "PauseManager.h"
#include "GameManager.h"
class Game;
class MainManager
{
	public:
		MainManager(Game* _game);
		void init();
		void update(float _deltaTime);
		void draw();
		void onPausePressed();
		void onMouseClicked(sf::Event _event);
		void onMouseMoved(sf::Event _event);
		bool  isPaused() const {
			return m_currentStateManager == m_pauseManager.get();
		}

		GameManager& getGameManager() {
			return *m_gameManager.get();
		}
	private:
		Game* m_game;

		std::unique_ptr<TitleScreenManager> m_titleScreenManager;
		std::unique_ptr<PreparationManager> m_preparationManager;
		std::unique_ptr<PauseManager> m_pauseManager;
		std::unique_ptr<GameManager> m_gameManager;

		GameStateManager* m_currentStateManager;
			
		void changeState(GameStateManager* _newState);
		
		
};

