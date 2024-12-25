#include "Game.h"

Game::Game(const std::string& _windowName) 
	: m_windowName(_windowName)
	, m_window(sf::VideoMode(1280, 720), m_windowName)
	, m_circle(100.f)
{
	//m_windowName = _windowName; 
	m_circle.setFillColor(sf::Color::Green); 
}
void Game::run() {
	
	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
		}
		this->draw();
		
	}

}
void Game :: draw() {
	m_window.clear();
	m_window.draw(m_circle);
	m_window.display();
}