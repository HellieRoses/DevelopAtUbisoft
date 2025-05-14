#include <iostream>
#include "Game.h"
int main()
{
	Game& game = Game::get();
	game.init("Jeu");
	game.run();
	return 0;
}