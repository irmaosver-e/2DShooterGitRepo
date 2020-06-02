#include "Game.h"
#include "SDLSystem.h"
#include <iostream>

int main(int argc, char* args[])
{
	if (TheGame::Instance().init()) //init the Game
	{
		while (TheGame::Instance().running())
		{
			if (TheSDLSystem::Instance().capFrameRate())
			{
				TheGame::Instance().handleEvents();
				TheGame::Instance().update();
				TheGame::Instance().render();
			}
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