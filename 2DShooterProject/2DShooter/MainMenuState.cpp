#include "MainMenuState.h"

#include "GameStateMachine.h"
#include "PlayState.h"


const std::string MainMenuState::s_menuID = "MENU";

bool MainMenuState::onEnter()
{
	GameState::onEnter();

	m_callbacks.push_back(0); //pushback 0 callbackID start from 1
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);

	//set the callbacks for menu items
	setCallbacks(m_callbacks);

	m_loadingComplete = true;
	std::cout << "MainMenuState::onEnter() - Entering MainMenuState \n";

	return true;
}

void MainMenuState::s_menuToPlay()
{
	TheGameStateMachine::Instance().changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
	TheGameStateMachine::Instance().quit();
}
