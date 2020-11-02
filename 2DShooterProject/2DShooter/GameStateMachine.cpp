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
	// if only pushing the state store the previous state for poping
	if (!m_changingState && !m_gameStates.empty())
	{
		m_pPreviousState = m_pCurrentState;
	}

	//checks if the state already exists
	for (GameState* state : m_gameStates)
	{
		if (state->getStateID() == pState->getStateID())
		{
			//the state exists already use it instead
			m_pCurrentState = state;
			
			//probably not enter but restart needs checking!!!!!!!!!!!!!1
			m_pCurrentState->onEnter();
		
			return;
		}
	}

	//parse state if non existent
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
			if (m_pPreviousState)
			{
				m_pPreviousState->onExit();
			}
		}
		else
		{
			m_pCurrentState = m_pPreviousState;
			m_pCurrentState->resume();
		}

		m_pPreviousState = nullptr;
	}
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
	m_changingState = true;
	popState();

	m_pCurrentState = nullptr;

	for (GameState* state : m_gameStates)
	{
		state->onExit();

		delete state;
	}

	m_gameStates.clear();
}
