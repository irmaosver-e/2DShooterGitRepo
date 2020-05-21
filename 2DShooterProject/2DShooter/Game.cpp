#include "Game.h"

#include <iostream>

#include "SoundManager.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "GameObjectFactory.h"
#include "MainMenuState.h"
#include "GameOverState.h"
#include "AnimatedGraphic.h"
#include "ScrollingBackground.h"
#include "MenuButton.h"
#include "Player.h"
#include "RoofTurret.h"
#include "ShotGlider.h"
#include "Eskeletor.h"
#include "Level1Boss.h"

//Define static instance
Game* Game::s_pInstance = nullptr;

Game::Game() :
	m_pWindow(0),
	m_pRenderer(0),
	m_bRunning(false),
	m_pGameStateMachine(0),
	m_playerLives(3),
	m_scrollSpeed((float)0.8),
	m_bLevelComplete(false),
	m_bChangingState(false)
{
	// add some level files to an array
	m_levelFiles.push_back("assets/map1.tmx");
	m_levelFiles.push_back("assets/map2.tmx");

	// start at this level
	m_currentLevel = 1;
}

Game::~Game()
{
	// we must clean up after ourselves to prevent memory leaks
	m_pRenderer = nullptr;
	m_pWindow = nullptr;
}

Game* Game::Instance()
{
	if (!s_pInstance)
	{
		s_pInstance = new Game();
	}
	return s_pInstance;
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen)
{
	//sets flag to fullscreen
	int flags = 0;

	// store the game width and height
	m_gameHeight = height;
	m_gameWidth = width;

	if (fullScreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	//attempt to initialize SDL
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

	// add some sound effects - TODO move to better place
	TheSoundManager::Instance()->load("assets/DST_ElectroRock.ogg", "music1", SOUND_MUSIC);
	TheSoundManager::Instance()->load("assets/boom.wav", "explode", SOUND_SFX);
	TheSoundManager::Instance()->load("assets/phaser.wav", "shoot", SOUND_SFX);
	
	TheSoundManager::Instance()->playMusic("music1", -1);

	//TheInputHandler::Instance()->initialiseJoysticks();

	// register the types for the game
	TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
	TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
	TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
	TheGameObjectFactory::Instance()->registerType("ScrollingBackground", new ScrollingBackgroundCreator());
	TheGameObjectFactory::Instance()->registerType("Turret", new TurretCreator());
	TheGameObjectFactory::Instance()->registerType("Glider", new GliderCreator());
	TheGameObjectFactory::Instance()->registerType("ShotGlider", new ShotGliderCreator());
	TheGameObjectFactory::Instance()->registerType("RoofTurret", new RoofTurretCreator());
	TheGameObjectFactory::Instance()->registerType("Eskeletor", new EskeletorCreator());
	TheGameObjectFactory::Instance()->registerType("Level1Boss", new Level1BossCreator());


	// start the menu state
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MainMenuState());

	m_bRunning = true; //everything inited successfully, start the main loop

	return true;
}

void Game::render()
{
	//clear the renderer to the draw colour
	SDL_RenderClear(m_pRenderer);

	m_pGameStateMachine->render();

	//draw to the window
	SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
	m_pGameStateMachine->update();
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();
}

void Game::clean()
{
	std::cout << "cleaning game\n";

	TheInputHandler::Instance()->clean();

	m_pGameStateMachine->clean();

	m_pGameStateMachine = nullptr;
	delete m_pGameStateMachine;

	TheTextureManager::Instance()->clearTextureMap();

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::setCurrentLevel(int currentLevel)
{
	m_currentLevel = currentLevel;
	m_pGameStateMachine->changeState(new GameOverState());
	m_bLevelComplete = false;
}
