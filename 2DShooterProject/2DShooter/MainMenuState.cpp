#include "MainMenuState.h"

#include "TextureManager.h"
#include "Game.h"
#include "StateParser.h"

#include "MenuButton.h"
#include "PlayState.h"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::update()
{
	if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_SPACE))
	{
		s_menuToPlay();
	}

	if (!m_gameObjects.empty())
	{
		for (unsigned int i = 0; i < m_gameObjects.size(); i++)
		{
			if (m_gameObjects[i] != 0)
			{
				m_gameObjects[i]->update();
			}
		}
	}
}

void MainMenuState::render()
{
	if (m_loadingComplete && !m_gameObjects.empty())
	{
		for (unsigned int i = 0; i < m_gameObjects.size(); i++)
		{
			m_gameObjects[i]->draw();
		}
	}
}

bool MainMenuState::onEnter()
{
	//parse the state
	StateParser stateParser;
	stateParser.parseState("assets/attack.xml", s_menuID, &m_gameObjects, &m_textureIDList);
	m_callbacks.push_back(0); //pushback 0 callbackID start from 1
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);

	//set the callbacks for menu items
	setCallbacks(m_callbacks);

	m_loadingComplete = true;
	std::cout << "Entering MainMenuState \n";

	return true;
}

bool MainMenuState::onExit()
{
	m_exiting = true;

	// clean the game objects
	if (m_loadingComplete && !m_gameObjects.empty())
	{
		m_gameObjects.back()->clean();
		m_gameObjects.pop_back();
	}

	m_gameObjects.clear();

	// reset the input handler
	TheInputHandler::Instance().reset();

	std::cout << "Exiting menu state \n";
	return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
	//go through the game objects
	if (!m_gameObjects.empty())
	{
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
}

void MainMenuState::s_menuToPlay()
{
	TheGame::Instance().getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
	TheGame::Instance().quit();
}
