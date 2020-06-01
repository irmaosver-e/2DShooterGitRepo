#include "SDLSystem.h"
#include <iostream>

SDLSystem::SDLSystem(token) : m_pWindow(nullptr), m_pRenderer(nullptr) 
{
}

SDLSystem::~SDLSystem()
{
	// we must clean up after ourselves to prevent memory leaks
	m_pRenderer = nullptr;
	m_pWindow = nullptr;
}

bool SDLSystem::init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen)
{
	//sets flag to fullscreen
	int flags = 0;

	// store the game width and height
	m_screenWidth = width;
	m_screenHeight = height;

	if (fullScreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	//attempt to initialize SDL if not present
	if (!SDL_Init(SDL_INIT_EVERYTHING))
	{
		//init the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (m_pWindow) //window init success
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

			if (m_pRenderer) //renderer init success
			{
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; //renderer init fail
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; //window init fail
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // sdl init fail
	}

	return true;
}

void SDLSystem::quit()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
