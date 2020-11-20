static int s_allocCounter;

#include "Game.h"
#include <iostream>


void* operator new (size_t size)
{
	s_allocCounter++;
	return malloc(size);
}

void operator delete(void* memory, size_t size)
{
	s_allocCounter--;

	if (s_allocCounter < 25)
	{
		std::cout << " allocations = " << s_allocCounter << "\n";
	}

	free(memory);
}

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
	}
	else
	{
		std::cout << "game init failure - \n";
		return -1;
	}


	game.clean();
	
	return 0;
}