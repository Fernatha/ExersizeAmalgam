#include "Game.h"

#include <stdexcept>
#include <iostream>
#include <cstdio>

int main()
{
	try
	{
		Game game;
		game.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}