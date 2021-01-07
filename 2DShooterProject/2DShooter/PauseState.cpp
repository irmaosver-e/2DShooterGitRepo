#include "PauseState.h"

#include "GameStateMachine.h"

#include "InputHandler.h"
#include "SoundManager.h"

const std::string PauseState::s_pauseID = "PAUSE";

bool PauseState::onEnter()
{
	TheInputHandler::Instance().reset();

	GameState::onEnter();

	if (m_callbacks.empty())
	{
		m_callbacks.push_back(0);
		m_callbacks.push_back(s_pauseToMain);
		m_callbacks.push_back(s_resumePlay);

		setCallbacks(m_callbacks);
	}

	m_loadingComplete = true;

	std::cout << "entering PauseState\n";
	std::cout << "unPause sound hardcoded in PauseState::update() \n";
	return true;
}

bool PauseState::onExit()
{
	GameState::onExit();

	return false;
}

/*
bool PauseState::update()
{
	if (GameState::update())
	{
		if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_RETURN))
		{
			TheSoundManager::Instance().playSound("unPause", 0);
			s_resumePlay();
		}

		return true;
	}
	return false;
}
*/

void PauseState::s_pauseToMain()
{
	TheGameStateMachine::Instance().changeState(MAIN);
}

void PauseState::s_resumePlay()
{
	TheGameStateMachine::Instance().popState();
}
