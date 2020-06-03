#include "Game.h"
#include <iostream>

const char* CONFIG_FILE = "config.xml";

int main(int argc, char* args[])
{
	if (TheGame::Instance().init(CONFIG_FILE)) //init the Game
	{
		while (TheGame::Instance().isRunning())
		{
			TheGame::Instance().run();
		}
	}
	else
	{
		std::cout << "game init failure - \n";
		return -1;
	}

	TheGame::Instance().clean();

	return 0;
}