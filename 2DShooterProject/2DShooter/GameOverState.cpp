#include "GameOverState.h"

#include "GameStateMachine.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

bool GameOverState::onEnter()
{
	GameState::onEnter();

	//only load the vector once
	if (m_callbacks.empty())
	{
		m_callbacks.push_back(0);
		m_callbacks.push_back(s_gameOverToMain);
		m_callbacks.push_back(s_restartPlay);

		// set the callbacks for menu items
		setCallbacks(m_callbacks);
	}

	m_loadingComplete = true;

	std::cout << "entering GameOverState\n";
	return true;
}

void GameOverState::s_gameOverToMain()
{
	TheGameStateMachine::Instance().changeState(MAIN);
}

void GameOverState::s_restartPlay()
{
	TheGameStateMachine::Instance().changeState(PLAY);
}



