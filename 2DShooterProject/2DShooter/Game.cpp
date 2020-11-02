#include "Game.h"

#include <iostream>

#include "SDLSystem.h"
#include "SystemParser.h"
#include "TextureManager.h"
#include "TextManager.h"
#include "ParserManager.h"
#include "InputHandler.h"
#include "GameObjectFactory.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "GameOverState.h"
#include "PlayState.h"
#include "TextBox.h"
#include "AnimatedGraphic.h"
#include "ScrollingBackground.h"
#include "HUD.h"
#include "Bullet.h"
#include "MenuButton.h"
#include "Player.h"
#include "Cursor.h"
#include "RoofTurret.h"
#include "ShotGlider.h"
#include "Eskeletor.h"
#include "Level1Boss.h"

Game::Game() :
	m_bRunning(false){}

bool Game::init(const char* configFile)
{	
	if (TheParserManager::Instance().getSystemParserRef().parseSystem(configFile))
	{
		registerObjTypes();

		TheGameStateMachine::Instance().changeState(new MainMenuState());

		m_bRunning = true; //everything inited successfully, start the main loop
	}

	return m_bRunning;
}

void Game::run()
{
	if (TheSDLSystem::Instance().capFrameRate())
	{
		handleEvents();
		update();
		render();
	}
	
	if (TheGameStateMachine::Instance().getQuitStates())
	{
		m_bRunning = false;
	}
}

void Game::render()
{
	//clear the renderer to the draw colour
	TheSDLSystem::Instance().clearScreen();

	TheGameStateMachine::Instance().render();

	//draw to the window
	TheSDLSystem::Instance().drawScreen();
}

void Game::update()
{
	TheGameStateMachine::Instance().update();
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
	TheGameObjectFactory::Instance().registerType("HUD", new ObjCreator<HUD>);
	TheGameObjectFactory::Instance().registerType("Cursor", new ObjCreator<Cursor>);
	TheGameObjectFactory::Instance().registerType("TextBox", new ObjCreator<TextBox>);
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

	TheGameStateMachine::Instance().clean();

	TheTextureManager::Instance().clearTextureMap();

	TheGameObjectFactory::Instance().clearCreators();

	TheTextManager::Instance().quit();

	//thesoundMAnager.quit ??

	TheSDLSystem::Instance().quit();
}

/*
void Game::setCurrentLevel(int currentLevel)
{
	m_currentLevel = currentLevel;
	TheGameStateMachine::Instance().reloadState();
	m_bLevelComplete = false;
}
*/
/*
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
*/
