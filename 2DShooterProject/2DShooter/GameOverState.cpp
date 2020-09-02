#include "GameOverState.h"

#include "MainMenuState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "AnimatedGraphic.h"
#include "Game.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "StateParser.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update()
{
	if (m_loadingComplete && !m_exiting)
	{
		GameState::update();
	}
	/*
	if (m_loadingComplete && !m_gameObjects.empty())
	{
		for (unsigned int i = 0; i < m_gameObjects.size(); i++)
		{
			m_gameObjects[i]->update();
		}
	}
	*/
}

void GameOverState::render()
{
	if (m_loadingComplete)
	{
		GameState::render();
	}

	/*
	if (m_loadingComplete && !m_gameObjects.empty())
	{
		for (unsigned int i = 0; i < m_gameObjects.size(); i++)
		{
			m_gameObjects[i]->draw();
		}
	}
	*/
}

bool GameOverState::onEnter()
{
	// to be updated with a LevelParser
	//StateParser stateParser;
	//stateParser.parseState(TheGame::Instance().getAssetsRoot(), TheGame::Instance().getStatesFile(), s_gameOverID, &m_gameObjects, &m_textureIDList);
	LevelParser levelParser;
	m_pLevel = levelParser.parseLevel(m_stageAssetsPath, m_stageMapFile);

	TheCollisionManager::Instance().setCurrentLevel(m_pLevel);


	m_callbacks.push_back(0);
	m_callbacks.push_back(s_gameOverToMain);
	m_callbacks.push_back(s_restartPlay);

	// set the callbacks for menu items
	setCallbacks(m_callbacks);

	m_loadingComplete = true;

	std::cout << "entering GameOverState\n";
	return true;
}

bool GameOverState::onExit()
{
	if (m_loadingComplete && !m_gameObjects.empty())
	{
		for (unsigned int i = 0; i < m_gameObjects.size(); i++)
		{
			m_gameObjects[i]->clean();
			delete m_gameObjects[i];
		}

		m_gameObjects.clear();
	}

	std::cout << m_gameObjects.size();

	// clear the texture manager
	for (unsigned int i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance().clearFromTextureMap(m_textureIDList[i]);
	}

	TheInputHandler::Instance().reset();

	std::cout << "exiting GameOverState\n";
	return true;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
	//go through the game objects
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		// if they are of type menu button assign callbacks based on IDs
		if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}

void GameOverState::s_gameOverToMain()
{
	TheGame::Instance().getStateMachine()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay()
{
	TheGame::Instance().getStateMachine()->changeState(new PlayState());
}



