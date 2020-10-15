#include "Game.h"

#include <iostream>

#include "SDLSystem.h"
#include "SystemParser.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "GameObjectFactory.h"
#include "MainMenuState.h"
#include "GameOverState.h"
#include "PlayState.h"
#include "AnimatedGraphic.h"
#include "ScrollingBackground.h"
#include "Bullet.h"
#include "MenuButton.h"
#include "Player.h"
#include "Cursor.h"
#include "RoofTurret.h"
#include "ShotGlider.h"
#include "Eskeletor.h"
#include "Level1Boss.h"

Game::Game(token) :
	m_bRunning(false),
	m_pGameStateMachine(0),
	m_scrollSpeed((float)1.8),
	m_bLevelComplete(false),
	m_bChangingState(false),
	m_currentLevel(1)
{
	std::cout << "m_scrollSpeed((float)1.8) HORDCODED in Game::Game \n";
}

bool Game::init(const char* configFile)
{	
	SystemParser sysParser;
	sysParser.parseSystem(configFile);

	registerObjTypes();

	// start the menu state
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MainMenuState());

	m_bRunning = true; //everything inited successfully, start the main loop

	return true;
}

void Game::run()
{
	if (TheSDLSystem::Instance().capFrameRate())
	{
		handleEvents();
		update();
			render();
	}
}

void Game::render()
{
	//clear the renderer to the draw colour
	TheSDLSystem::Instance().clearScreen();

	m_pGameStateMachine->render();

	//draw to the window
	TheSDLSystem::Instance().drawScreen();
}

void Game::update()
{
	m_pGameStateMachine->update();
}

void Game::handleEvents()
{
	TheInputHandler::Instance().update();
}

void Game::registerObjTypes()
{
	// register the types for the game
	TheGameObjectFactory::Instance().registerType("MenuButton", new ObjCreator<MenuButton>);
	TheGameObjectFactory::Instance().registerType("Player", new ObjCreator<Player>);
	TheGameObjectFactory::Instance().registerType("Cursor", new ObjCreator<Cursor>);
	TheGameObjectFactory::Instance().registerType("AnimatedGraphic", new ObjCreator<AnimatedGraphic>);
	TheGameObjectFactory::Instance().registerType("ScrollingBackground", new ObjCreator<ScrollingBackground>);
	TheGameObjectFactory::Instance().registerType("PlayerBullet", new ObjCreator<PlayerBullet>);
	TheGameObjectFactory::Instance().registerType("EnemyBullet", new ObjCreator<EnemyBullet>);
	TheGameObjectFactory::Instance().registerType("Turret", new ObjCreator<Turret>);
	TheGameObjectFactory::Instance().registerType("RoofTurret", new ObjCreator<RoofTurret>);
	TheGameObjectFactory::Instance().registerType("Glider", new ObjCreator<Glider>);
	TheGameObjectFactory::Instance().registerType("ShotGlider", new ObjCreator<ShotGlider>);
	TheGameObjectFactory::Instance().registerType("Eskeletor", new ObjCreator<Eskeletor>);
	TheGameObjectFactory::Instance().registerType("Level1Boss", new ObjCreator<Level1Boss>);
}

void Game::clean()
{
	std::cout << "cleaning game\n";

	TheInputHandler::Instance().clean();

	m_pGameStateMachine->clean();

	m_pGameStateMachine = nullptr;
	delete m_pGameStateMachine;

	TheTextureManager::Instance().clearTextureMap();

	TheSDLSystem::Instance().quit();
}

void Game::setCurrentLevel(int currentLevel)
{
	m_currentLevel = currentLevel;
	m_pGameStateMachine->reloadState();
	m_bLevelComplete = false;
}

void Game::addLevelFile(int levelNumber, std::string filename)
{
	std::map<int, std::string>::iterator it = m_levelFiles.find(levelNumber);
	
	//does nothing if the level file is repeated
	if (it == m_levelFiles.end())
	{
		//file not in map 
		m_levelFiles[levelNumber] = filename;
	}
}
