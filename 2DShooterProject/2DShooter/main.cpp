#include "SDL.h"
#include "Game.h"
#include <iostream>

const char* CONFIG_FILE = "config.xml";

int main(int argc, char* args[])
{
	Game game;

	if (game.init(CONFIG_FILE)) //init the Game
	{
		while (game.isRunning())
		{
			game.run();
		}

		game.clean();
	}
	else
	{
		std::cout << "game init failure - \n";
		return -1;
	}	

	return 0;
}