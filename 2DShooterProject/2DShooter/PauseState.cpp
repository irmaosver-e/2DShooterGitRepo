#include "PauseState.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::update()
{
	if (m_loadingComplete && !m_exiting)
	{
		GameState::update();
	}
}

void PauseState::render()
{
	if (m_loadingComplete)
	{
		GameState::render();
	}
}

bool PauseState::onEnter()
{
	LevelParser levelParser;
	m_pLevel = levelParser.parseLevel(m_stageAssetsPath, m_stageMapFile);

	TheCollisionManager::Instance().setCurrentLevel(m_pLevel);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_pauseToMain);
	m_callbacks.push_back(s_resumePlay);

	setCallbacks(m_callbacks);

	m_loadingComplete = true;

	std::cout << "entering PauseState\n";
	return true;
}

bool PauseState::onExit()
{
	// needs revising
	/*
	if (m_loadingComplete && !m_gameObjects.empty())
	{
		for (unsigned int i = 0; i < m_gameObjects.size(); i++)
		{
			m_gameObjects[i]->clean();
			delete m_gameObjects[i];
		}
		m_gameObjects.clear();
	}
	// clear the texture manager
	for (unsigned int i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance().clearFromTextureMap(m_textureIDList[i]);
	}
	*/

	TheInputHandler::Instance().reset();

	std::cout << "exiting PauseState\n";
	return true;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
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

void PauseState::s_pauseToMain()
{
	TheGame::Instance().getStateMachine()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay()
{
	TheGame::Instance().getStateMachine()->popState();
}
