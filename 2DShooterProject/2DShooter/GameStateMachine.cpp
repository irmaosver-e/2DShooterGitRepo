#include "GameStateMachine.h"

#include <iostream>
#include "StateParser.h"

void GameStateMachine::changeState(GameState* pState)
{
	m_changingState = true;

	if (!m_gameStates.empty())
	{
		// trying to change to same state - do nothing
		if (m_pCurrentState->getStateID() == pState->getStateID())
		{
			std::cout << " in GameStateMachine::changeState - changing to same state as current \n";
			std::cout << "change state: " << pState->getStateID() << "\n";
			return;
		}
	}

	popState();

	pushState(pState);

	m_changingState = false;
}

void GameStateMachine::pushState(GameState* pState)
{
	if (!m_changingState)
	{
		m_previousStates.push_back(m_pCurrentState);
	}

	//checks if the state already exists
	for (GameState* state : m_gameStates)
	{
		if (state->getStateID() == pState->getStateID())
		{
			//the state exists already use it instead
			m_pCurrentState = state;
			
			m_pCurrentState->onEnter();
		
			return;
		}
	}

	//parse state here
	StateParser stateParser;
	stateParser.parseState(pState);

	m_gameStates.push_back(pState);

	m_pCurrentState = m_gameStates.back();

	m_pCurrentState->onEnter();
}

void GameStateMachine::popState()
{
	if (!m_gameStates.empty())
	{
		m_pCurrentState->onExit();

		if (m_changingState)
		{
			m_previousStates.push_back(m_pCurrentState);
		}
		else
		{
			m_pCurrentState = m_previousStates.back();
			m_previousStates.pop_back();

			m_pCurrentState->resume();
		}
	}

	/*
	if (!m_gameStates.empty())
	{
		m_pCurrentState->onExit();

		//swap states
		GameState* pTempSate = m_pPreviousState;
		m_pCurrentState = m_pPreviousState;
		m_pPreviousState = pTempSate;
		//m_gameStates.pop_back();

		if (!m_changingState)
		{
			m_pCurrentState->resume();
		}
	}
	*/
}

void GameStateMachine::reloadState()
{
	m_pCurrentState->onEnter();
}

void GameStateMachine::update()
{
	if (!m_gameStates.empty())
	{
		m_pCurrentState->update();
	}
}

void GameStateMachine::render()
{
	if (!m_gameStates.empty())
	{
		m_pCurrentState->render();
	}
}

void GameStateMachine::clean()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->onExit();

		delete m_gameStates.back();

		m_gameStates.clear();
	}
}
