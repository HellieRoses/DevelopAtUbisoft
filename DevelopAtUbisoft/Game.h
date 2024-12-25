#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class Game {
	public:
		Game(const std::string& _windowName);
		void run();
	private:
		void draw();
		std :: string m_windowName;
		sf::RenderWindow m_window;
		sf::CircleShape m_circle;
};