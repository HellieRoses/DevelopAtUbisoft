#include <iostream>
#include "Game.h"
int main()
{
	std::cout << "Hello World" << std::endl; // console.log(...)
	Game& game = Game::get();
	game.init("Jeu");
	game.run();
	return 0;
}