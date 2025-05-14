#include "MainManager.h"
#include "Game.h"
#include "Thief.h"
#include <SFML/Window/Cursor.hpp>

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
	if (m_currentStateManager == m_gameManager.get()) {
		if (m_gameManager->isGameFinished()) {
			_newState = m_titleScreenManager.get();
			m_gameManager->resetGame();
		}
	}

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
			m_gameManager->resetGame();
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
		sf::Vector2i mousePos = sf::Mouse::getPosition(m_game->getGameWindow());
		if (m_currentStateManager == m_titleScreenManager.get())
		{
			sf::Sprite button = m_titleScreenManager->getCreditsButtonSprite();
			sf::Sprite panel = m_titleScreenManager->getPanelSprite();

			sf::FloatRect rectB = button.getLocalBounds();
			sf::Vector2f spritePosB = button.getPosition() - button.getOrigin();
			sf::Vector2f rectSizeB = rectB.getSize();
			sf::Vector2f spriteScaleB = button.getScale();
			sf::Vector2f rectScaledB = { rectSizeB.x * spriteScaleB.x, rectSizeB.y * spriteScaleB.y };

			sf::FloatRect rectP = panel.getLocalBounds();
			sf::Vector2f spritePosP = panel.getPosition() - panel.getOrigin();
			sf::Vector2f rectSizeP = rectP.getSize();
			sf::Vector2f spriteScaleP = panel.getScale();
			sf::Vector2f rectScaledP = { rectSizeP.x * spriteScaleP.x, rectSizeP.y * spriteScaleP.y };

			bool isMouseCloseToButtonx = spritePosB.x <= mousePos.x && mousePos.x <= (spritePosB.x + rectScaledB.x);
			bool isMouseCloseToButtony = spritePosB.y <= mousePos.y && mousePos.y <= (spritePosB.y + rectScaledB.y);
			bool isMouseCloseToPanelx = spritePosP.x <= mousePos.x && mousePos.x <= (spritePosP.x + rectScaledP.x);
			bool isMouseCloseToPanely = spritePosP.y <= mousePos.y && mousePos.y <= (spritePosP.y + rectScaledP.y);
			if (isMouseCloseToButtonx && isMouseCloseToButtony) {
				m_titleScreenManager->clickOnCredit();
			}
			if (isMouseCloseToPanelx && isMouseCloseToPanely) {
				return;
			}else{
				changeState(m_preparationManager.get());
			}
		}
		else if (m_currentStateManager == m_preparationManager.get())
		{
			changeState(m_gameManager.get());
		}
		else if (m_currentStateManager == m_pauseManager.get())
		{
			changeState(m_gameManager.get());
		}
		else
		{
			m_gameManager->onMouseClicked(mousePos);
			
		}
	}
	else if (_event.mouseButton.button == sf::Mouse::Right)
	{
		if (m_currentStateManager == m_preparationManager.get())
		{
			sf::Vector2i localPosition = sf::Mouse::getPosition(m_game->getGameWindow());
			m_preparationManager->onMouseClicked(localPosition);
		}
	}
}

void MainManager::onMouseMoved(sf::Event _event)
{

	sf::Vector2i mousePos = sf::Mouse::getPosition(m_game->getGameWindow());
	sf::Cursor cursor;
	if (m_currentStateManager == m_gameManager.get()) {
		bool hoveringThief = false;
		m_game->visit<Thief>([this, mousePos, &hoveringThief](Thief& _thief) {
			sf::FloatRect rect = _thief.getSprite().getLocalBounds();
			sf::Vector2f spritePos = _thief.getSpritePos() - _thief.getSprite().getOrigin();
			sf::Vector2f rectSize = rect.getSize();
			bool isMouseCloseToThiefx = spritePos.x <= mousePos.x && mousePos.x <= (spritePos.x + rectSize.x);
			bool isMouseCloseToThiefy = spritePos.y <= mousePos.y && mousePos.y <= (spritePos.y + rectSize.y);
			if (isMouseCloseToThiefx && isMouseCloseToThiefy)
			{
				hoveringThief = true;
				return false;
			}
			return true;
			});
		if (hoveringThief) {
			if (cursor.loadFromSystem(sf::Cursor::Type::Hand))
			{
				m_game->getGameWindow().setMouseCursor(cursor);
			}

		}
		else {
			if (cursor.loadFromSystem(sf::Cursor::Type::Arrow))
			{
				m_game->getGameWindow().setMouseCursor(cursor);
			}
		}
	}
	else if (m_currentStateManager == m_preparationManager.get()) {
		uint tilePosX = static_cast<int>(std::floor(mousePos.x / (MINI_TILE_SIZE)));
		uint tilePosY = static_cast<int>(std::floor(mousePos.y / (MINI_TILE_SIZE)));
		if (tilePosX < TILE_X_MAX && tilePosY < TILE_Y_MAX) {
			if (TileMap::getTileAt(tilePosX, tilePosY) == 0) {
				if (cursor.loadFromSystem(sf::Cursor::Type::Hand))
				{
					m_game->getGameWindow().setMouseCursor(cursor);
				}
			}
			else {
				if (cursor.loadFromSystem(sf::Cursor::Type::Arrow))
				{
					m_game->getGameWindow().setMouseCursor(cursor);
				}
			}
		}
	}else if (m_currentStateManager == m_titleScreenManager.get()){
		bool hoveringButton = false;
		bool hoveringPanel = false;
		sf::Sprite button = m_titleScreenManager->getCreditsButtonSprite();
		sf::Sprite panel = m_titleScreenManager->getPanelSprite();

		sf::FloatRect rectB = button.getLocalBounds();
		sf::Vector2f spritePosB = button.getPosition() - button.getOrigin();
		sf::Vector2f rectSizeB = rectB.getSize();
		sf::Vector2f spriteScaleB = button.getScale();
		sf::Vector2f rectScaledB = { rectSizeB.x * spriteScaleB.x, rectSizeB.y * spriteScaleB.y };

		sf::FloatRect rectP = panel.getLocalBounds();
		sf::Vector2f spritePosP = panel.getPosition() - panel.getOrigin();
		sf::Vector2f rectSizeP = rectP.getSize();
		sf::Vector2f spriteScaleP = panel.getScale();
		sf::Vector2f rectScaledP = { rectSizeP.x * spriteScaleP.x, rectSizeP.y * spriteScaleP.y };

		bool isMouseCloseToButtonx = spritePosB.x <= mousePos.x && mousePos.x <= (spritePosB.x + rectScaledB.x);
		bool isMouseCloseToButtony = spritePosB.y <= mousePos.y && mousePos.y <= (spritePosB.y + rectScaledB.y);
		bool isMouseCloseToPanelx = spritePosP.x <= mousePos.x && mousePos.x <= (spritePosP.x + rectScaledP.x);
		bool isMouseCloseToPanely = spritePosP.y <= mousePos.y && mousePos.y <= (spritePosP.y + rectScaledP.y);

		if (isMouseCloseToButtonx && isMouseCloseToButtony) {
			hoveringButton = true;
		}
		else {
			hoveringButton = false;
		}
		if (isMouseCloseToPanelx && isMouseCloseToPanely) {
			hoveringPanel = true;
		}
		else {
			hoveringPanel = false;
		}

		if (hoveringButton) {
			if (cursor.loadFromSystem(sf::Cursor::Type::Hand))
			{
				m_game->getGameWindow().setMouseCursor(cursor);
			}
		}
		else if (!hoveringPanel) {
			if (cursor.loadFromSystem(sf::Cursor::Type::Hand))
			{
				m_game->getGameWindow().setMouseCursor(cursor);
			}
		}
		else
		{
			if (cursor.loadFromSystem(sf::Cursor::Type::Arrow))
			{
				m_game->getGameWindow().setMouseCursor(cursor);
			}
		}
	}
	
}
