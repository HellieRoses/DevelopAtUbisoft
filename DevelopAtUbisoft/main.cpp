#include <iostream>
#include "Game.h"
int main()
{
	std::cout << "Hello World" << std::endl; // console.log(...)
	Game game("Tower Defense");
	game.run();
	return 0;
}