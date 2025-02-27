#include "MainManager.h"
#include "Game.h"

MainManager::MainManager(Game* _game)
	: m_game(_game)
{
	m_titleScreenManager = std::make_unique< TitleScreenManager>(m_game);
	m_preparationManager = std::make_unique< PreparationManager>(m_game);
	m_pauseManager = std::make_unique<PauseManager>(m_game);
	m_gameManager = std::make_unique<GameManager>(m_game);
	m_currentStateManager = m_titleScreenManager.get();
}

void MainManager::onPausePressed()
{
	if (m_currentStateManager == m_pauseManager.get()) {
		changeState(m_gameManager.get());
	}
	else if (m_currentStateManager == m_gameManager.get())
	{
		changeState(m_pauseManager.get());
	}
}

void MainManager::changeState(GameStateManager* _newState)
{
	if (m_currentStateManager == _newState)
		return;
	//on exit current state

	if (m_currentStateManager == m_preparationManager.get())
	{
		m_gameManager->initLevel();
	}
	m_currentStateManager->onExitState();
	m_currentStateManager = _newState;
	//on enter current state
	m_currentStateManager->onEnterState();
	if (m_currentStateManager == m_titleScreenManager.get())
	{
		m_gameManager->resetGame();
	}
}

void MainManager::draw() {

	m_game->getGameWindow().display();
	m_game->getGameWindow().clear(sf::Color::Black);
	m_currentStateManager->drawState();
}

void MainManager::init()
{
	m_titleScreenManager->initText();
	m_preparationManager->initText();
	m_pauseManager->initText();
	m_gameManager->initText();
	m_titleScreenManager->onEnterState();
}

void MainManager::update(float _deltaTime) {
	//parcourt liste ennemis + mise à jour
	//delta time 

	m_currentStateManager->updateState(_deltaTime);

	if (m_currentStateManager == m_gameManager.get())
	{
		if (m_gameManager->playerLoose()) {
			changeState(m_titleScreenManager.get());
		}
		else if (m_gameManager->hasRoundFinished())
		{
			changeState(m_preparationManager.get());
		}
	}
}

void MainManager::onMouseClicked(sf::Event _event)
{
	if (_event.mouseButton.button == sf::Mouse::Left)
	{
		if (m_currentStateManager == m_titleScreenManager.get())
		{
			changeState(m_preparationManager.get());
		}
		else if (m_currentStateManager == m_preparationManager.get())
		{
			changeState(m_gameManager.get()); //TODO change
		}
		else if (m_currentStateManager == m_pauseManager.get())
		{
			changeState(m_gameManager.get());
		}
		else
		{
			
			sf::Vector2i localPosition = sf::Mouse::getPosition(m_game->getGameWindow());
			m_gameManager->onMouseClicked(localPosition);
			
		}
	}
}