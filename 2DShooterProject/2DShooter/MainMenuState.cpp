#include "MainMenuState.h"

#include "TextureManager.h"
#include "Game.h"
#include "InputHandler.h"
#include "StateParser.h"

#include "MenuButton.h"
#include "PlayState.h"

#include "CollisionManager.h"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::update()
{
	// to be implemented
	if (m_loadingComplete && !m_exiting)
	{
		GameState::update();
	}
}

void MainMenuState::render()
{
	if (m_loadingComplete)
	{
		GameState::render();
	}
}

bool MainMenuState::onEnter()
{
	LevelParser levelParser;
	m_pLevel = levelParser.parseLevel(m_stageAssetsPath, m_stageMapFile);

	TheCollisionManager::Instance().setCurrentLevel(m_pLevel);

	m_callbacks.push_back(0); //pushback 0 callbackID start from 1
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);

	//set the callbacks for menu items
	setCallbacks(m_callbacks);

	m_loadingComplete = true;
	std::cout << "MainMenuState::onEnter() - Entering MainMenuState \n";

	return true;
}

bool MainMenuState::onExit()
{
	m_exiting = true;

	// reset the input handler
	TheInputHandler::Instance().reset();

	std::cout << "MainMenuState::onExit() - Exiting menu state \n";
	return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
	std::vector<GameObject*> pObjectsContainer;
	m_pLevel->getObjectsfromLayers(pObjectsContainer);

	//go through the game objects
	if (!pObjectsContainer.empty())
	{
		for (unsigned int i = 0; i < pObjectsContainer.size(); i++)
		{
			// if they are of type menu button assign callbacks based on IDs
			if (dynamic_cast<MenuButton*>(pObjectsContainer[i]))
			{
				MenuButton* pButton = dynamic_cast<MenuButton*>(pObjectsContainer[i]);
				pButton->setCallback(callbacks[pButton->getCallbackID()]);
			}
		}
	}
}

void MainMenuState::s_menuToPlay()
{
	TheGame::Instance().getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
	TheGame::Instance().quit();
}
