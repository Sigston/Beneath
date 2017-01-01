#include "stdafx.h"
#include "Game.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//	All function is encapsulated within the Game class.
	Game game;

	if (!game.init())
	{
		std::cout << "Game failed to initialize." << std::endl;
		system("pause");
		return -1;
	}
	if (!game.loadLevel())
	{
		std::cout << "Game assets failed to load." << std::endl;
		system("pause");
		return -1;
	}
	
	game.run();
	return 0;
}

