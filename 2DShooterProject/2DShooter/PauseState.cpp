#include "PauseState.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::update()
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

void PauseState::render()
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

bool PauseState::onEnter()
{
	m_exiting = false;

	//parse the state
	StateParser stateParser;
	stateParser.parseState("test.xml", s_pauseID, &m_gameObjects, &m_textureIDList);
	m_callbacks.push_back(0); //pushback 0 callbackID start from 1
	m_callbacks.push_back(s_resumePlay);
	m_callbacks.push_back(s_pauseToMain);

	//set the callbacks for menu items
	setCallbacks(m_callbacks);

	std::cout << "entering PauseState \n";
	return true;
}

bool PauseState::onExit()
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

	//reset mouse button states
	TheInputHandler::Instance()->reset();

	std::cout << "Exiting pause state \n";
	return true;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
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

void PauseState::s_pauseToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay()
{
	TheGame::Instance()->getStateMachine()->popState();
}
