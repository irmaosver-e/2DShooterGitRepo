#include "PauseState.h"

#include "Game.h"
#include "MainMenuState.h"

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
	GameState::onEnter();

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_pauseToMain);
	m_callbacks.push_back(s_resumePlay);

	setCallbacks(m_callbacks);

	m_loadingComplete = true;

	std::cout << "entering PauseState\n";
	return true;
}

void PauseState::s_pauseToMain()
{
	TheGame::Instance().getStateMachine()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay()
{
	TheGame::Instance().getStateMachine()->popState();
}
