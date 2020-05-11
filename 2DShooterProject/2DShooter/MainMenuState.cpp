#include "MainMenuState.h"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::update()
{
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		if (m_exiting)
		{
			break;
		}
		m_gameObjects[i]->update();
	}
}

void MainMenuState::render()
{
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		if (m_exiting)
		{
			break;
		}
		m_gameObjects[i]->draw();
	}
}

bool MainMenuState::onEnter()
{
	m_exiting = false;

	//parse the state
	StateParser stateParser;
	stateParser.parseState("test.xml", s_menuID, &m_gameObjects, &m_textureIDList);
	m_callbacks.push_back(0); //pushback 0 callbackID start from 1
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);

	//set the callbacks for menu items
	setCallbacks(m_callbacks);

	std::cout << "Entering MainMenuState \n";

	return true;
}

bool MainMenuState::onExit()
{
	m_exiting = true;

	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();

	//clear the texture manager
	for (unsigned int i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}

	std::cout << "Exiting menu state \n";
	return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
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

void MainMenuState::s_menuToPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
	TheGame::Instance()->quit();
}
