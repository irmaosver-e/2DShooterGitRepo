#include "GameState.h"

#include "InputHandler.h"
#include "ParserManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"

void GameState::init()
{	
	//only parse once
	if (!m_pLevel)
	{
		m_pLevel = TheParserManager::Instance().getLevelParserRef().parseLevel();
	}
}

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
	//for debugging purposes
	std::cout << "Entering " << getStateID() << " State\n";
	
	//only parse once
	if (m_pLevel)
	{
		m_pLevel->onEnter();
		//needs to be moved to Level onExit
		//m_pLevel->reset();
	}



	TheCollisionManager::Instance().setCurrentLevel(m_pLevel);

	m_exiting = false;

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

	m_pLevel->onExit();

	TheInputHandler::Instance().reset();

	std::cout << "exiting " << getStateID() << " State\n";
	return true;
}

bool GameState::resume()
{
	TheSoundManager::Instance().resumeMusic();
	TheCollisionManager::Instance().setCurrentLevel(m_pLevel);

	return true;
}
