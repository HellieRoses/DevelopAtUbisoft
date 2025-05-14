#include "TitleScreenManager.h"
#include "Game.h"
#include <sstream>

TitleScreenManager::TitleScreenManager(Game* _game)
	: m_game(_game)
{
	initUIElements();
}

void TitleScreenManager::updateState(float _deltaTime)
{
	updateUIElements();
}

void TitleScreenManager::drawState()
{
	drawUIElements();
}

void TitleScreenManager::onEnterState()
{
	return;
}

void TitleScreenManager::onExitState()
{
	return;
}

void TitleScreenManager::initText()
{
	std::ostringstream m_titleString;
	m_titleString << "WELCOME TO";

	m_titleText.setString(m_titleString.str());
	m_titleText.setFont(m_game->getFont());
	m_titleText.setFillColor(sf::Color::White);
	m_titleText.setCharacterSize(30);
	m_titleText.setPosition(PANEL_POSI_X + 140, PANEL_POSI_Y + 20);
	m_titleText.setStyle(sf::Text::Bold);

	std::ostringstream m_titleStrin2;
	m_titleStrin2 << "BANK OUT";

	m_titleText2.setString(m_titleStrin2.str());
	m_titleText2.setFont(m_game->getFont());
	m_titleText2.setFillColor(sf::Color::White);
	m_titleText2.setCharacterSize(60);
	m_titleText2.setPosition(PANEL_POSI_X + 90, PANEL_POSI_Y + 60);
	m_titleText2.setStyle(sf::Text::Bold);

	std::ostringstream m_mainString;
	m_mainString << "In this game, you need to prevent\nthieves from escaping with your money.\n\n" << "Use turrets and your mouse\n to stop them !";

	m_mainText.setString(m_mainString.str());
	m_mainText.setFont(m_game->getFont());
	m_mainText.setFillColor(sf::Color::White);
	m_mainText.setCharacterSize(23);
	m_mainText.setPosition(PANEL_POSI_X + 15, PANEL_POSI_Y + 150);
	m_mainText.setLineSpacing(1.2f);

	std::ostringstream m_lastString;
	m_lastString << "Click anywhere to start the game !";

	m_lastText.setString(m_lastString.str());
	m_lastText.setFont(m_game->getFont());
	m_lastText.setFillColor(sf::Color::Green);
	m_lastText.setCharacterSize(23);
	m_lastText.setPosition(PANEL_POSI_X + 50, PANEL_POSI_Y + 425);

	std::ostringstream m_creditsStr;
	m_creditsStr << "Credits";
	sf::Color color(23, 47, 66);
	m_creditsButtonText.setString(m_creditsStr.str());
	m_creditsButtonText.setFont(m_game->getFont());
	m_creditsButtonText.setFillColor(color);
	m_creditsButtonText.setCharacterSize(23);
	m_creditsButtonText.setPosition(CREDIT_POS_X + (MINI_PANEL_SIZE_X * MINI_PANEL_SCALE_X * 1.2f) / 2 - 45, CREDIT_BASE_POS_Y + 10);
	
	std::ostringstream m_creditsTitleStr;
	m_creditsTitleStr << "CREDITS";

	m_creditsTitleText.setString(m_creditsTitleStr.str());
	m_creditsTitleText.setFont(m_game->getFont());
	m_creditsTitleText.setFillColor(sf::Color::White);
	m_creditsTitleText.setCharacterSize(40);
	m_creditsTitleText.setPosition(PANEL_POSI_X + 160, PANEL_POSI_Y + 20);

	std::ostringstream m_creditsDStr;
	m_creditsDStr << "Developers :\n" << "Maëlys Boissezon & Thibaut Magnier\n\n"<<"Background Design :\n"<< "Elliot Barthélémy";

	m_creditsText.setString(m_creditsDStr.str());
	m_creditsText.setFont(m_game->getFont());
	m_creditsText.setFillColor(sf::Color::White);
	m_creditsText.setCharacterSize(23);
	m_creditsText.setPosition(PANEL_POSI_X + 15, PANEL_POSI_Y + 150);

}

void TitleScreenManager::clickOnCredit()
{
	m_inCredit = !m_inCredit;
}

void TitleScreenManager::initUIElements()
{
	m_backgroundImage = sf::Sprite(m_game->getBackgroundTexture(), sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(BACKGROUND_SIZE_X, BACKGROUND_SIZE_Y)));
	m_backgroundImage.setScale({ BACKGROUND_SCALE, BACKGROUND_SCALE });

	m_widePanel = sf::Sprite(m_game->getPanelTexture(), sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(PANEL_SIZE_X, PANEL_SIZE_Y)));
	m_widePanel.setScale({ 2.f,2.5f });
	m_widePanel.setPosition({ PANEL_POSI_X, PANEL_POSI_Y });


	m_creditsButton = sf::Sprite(m_game->getBluePanelTexture(), sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(MINI_PANEL_SIZE_X, MINI_PANEL_SIZE_Y)));
	m_creditsButton.setPosition({  CREDIT_POS_X, CREDIT_BASE_POS_Y });
	m_creditsButton.setScale(MINI_PANEL_SCALE_X * 1.2f, MINI_PANEL_SCALE_Y * 1.2f);

	
}

void TitleScreenManager::updateUIElements()
{

	std::ostringstream m_creditsStr;
	if (!m_inCredit) {
		m_creditsStr << "Credits";
		m_creditsButtonText.setPosition(CREDIT_POS_X + (MINI_PANEL_SIZE_X * MINI_PANEL_SCALE_X * 1.2f) / 2 - 45, CREDIT_BASE_POS_Y + 10);
		m_creditsButton.setPosition({ CREDIT_POS_X, CREDIT_BASE_POS_Y });
	}
	else {
		m_creditsStr << "Back To Menu";
		m_creditsButtonText.setPosition(CREDIT_POS_X + (MINI_PANEL_SIZE_X * MINI_PANEL_SCALE_X * 1.2f) / 2 - 75, CREDIT_OTHER_POS_Y + 10);
		m_creditsButton.setPosition({ CREDIT_POS_X, CREDIT_OTHER_POS_Y });
	}
	m_creditsButtonText.setString(m_creditsStr.str());

}

void TitleScreenManager::drawUIElements()
{
	m_game->getGameWindow().draw(m_backgroundImage);
	m_game->getGameWindow().draw(m_widePanel);

	if (!m_inCredit) {

		m_game->getGameWindow().draw(m_titleText);
		m_game->getGameWindow().draw(m_titleText2);
		m_game->getGameWindow().draw(m_mainText);
		m_game->getGameWindow().draw(m_lastText);
	}
	else {
		m_game->getGameWindow().draw(m_creditsTitleText);
		m_game->getGameWindow().draw(m_creditsText);
	}

	m_game->getGameWindow().draw(m_creditsButton);
	m_game->getGameWindow().draw(m_creditsButtonText);


	if (m_game->isDrawDebug()) {
		sf::RectangleShape debugShape;
		debugShape.setOrigin(m_creditsButton.getOrigin());
		debugShape.setRotation(m_creditsButton.getRotation());
		debugShape.setPosition(m_creditsButton.getPosition());
		debugShape.setOutlineColor(sf::Color::Red);
		debugShape.setFillColor(sf::Color::Transparent);
		debugShape.setOutlineThickness(2.0f);
		debugShape.setSize(m_creditsButton.getLocalBounds().getSize());
		debugShape.setScale(m_creditsButton.getScale());
		m_game->getGameWindow().draw(debugShape);

		sf::RectangleShape debugShape2;
		debugShape2.setOrigin(m_widePanel.getOrigin());
		debugShape2.setRotation(m_widePanel.getRotation());
		debugShape2.setPosition(m_widePanel.getPosition());
		debugShape2.setOutlineColor(sf::Color::Black);
		debugShape2.setFillColor(sf::Color::Transparent);
		debugShape2.setOutlineThickness(2.0f);
		debugShape2.setSize(m_widePanel.getLocalBounds().getSize());
		debugShape2.setScale(m_widePanel.getScale());
		m_game->getGameWindow().draw(debugShape2);
	}

}

