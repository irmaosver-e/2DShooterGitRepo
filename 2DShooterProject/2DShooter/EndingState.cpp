#include "EndingState.h"
#include "GameStateMachine.h"

const std::string EndingState::s_endingID = "ENDING";

bool EndingState::onEnter()
{
	GameState::onEnter();

	//only load the vector once
	if (m_callbacks.empty())
	{
		m_callbacks.push_back(0);
		m_callbacks.push_back(s_gameOverToMain);

		// set the callbacks for menu items
		setCallbacks(m_callbacks);
	}

	m_loadingComplete = true;

	std::cout << "entering EndingState\n";
	return true;
}

void EndingState::s_gameOverToMain()
{
	TheGameStateMachine::Instance().changeState(MAIN);
}




