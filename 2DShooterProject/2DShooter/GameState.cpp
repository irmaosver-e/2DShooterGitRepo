#include "GameState.h"

#include "InputHandler.h"
#include "LevelParser.h"
#include "CollisionManager.h"

bool GameState::update()
{
	if (m_loadingComplete && !m_exiting)
	{
		if (m_pLevel)
		{
			m_pLevel->update();
			return true;
		}
	}
	return false;
}

bool GameState::render()
{
	if (m_loadingComplete)
	{
		if (m_pLevel != 0)
		{
			m_pLevel->render();
			return true;
		}
	}
	return false;
}

bool GameState::onEnter()
{
	LevelParser levelParser;
	m_pLevel = levelParser.parseLevel(m_stageAssetsPath, m_stageMapFile);

	TheCollisionManager::Instance().setCurrentLevel(m_pLevel);

	return true;
}

bool GameState::onExit()
{		// needs revising
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

		// pop m_callbacks????

	m_exiting = true;

	TheInputHandler::Instance().reset();

	std::cout << "exiting " << getStateID() << " State\n";
	return true;
}

bool GameState::resume()
{
	TheCollisionManager::Instance().setCurrentLevel(m_pLevel);

	return true;
}
