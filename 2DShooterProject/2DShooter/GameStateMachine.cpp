#include "GameStateMachine.h"

#include <iostream>

void GameStateMachine::changeState(GameState* pState)
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->getStateID() == pState->getStateID())
		{
			// trying to change to same state - do nothing
			std::cout << " in GameStateMachine::changeState - changing to same state as current \n";
			std::cout << "change state: " << pState->getStateID() << "\n";
			return; 
		}

		m_gameStates.back()->onExit();
		m_gameStates.pop_back();
	}

	// initialise it
	pState->onEnter();

	// push back our new state
	m_gameStates.push_back(pState);
}

void GameStateMachine::pushState(GameState* pState)
{
	m_gameStates.push_back(pState);
	m_gameStates.back()->onEnter();
}

void GameStateMachine::popState()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->onExit();
		m_gameStates.pop_back();
	}

	m_gameStates.back()->resume();
}

void GameStateMachine::reloadState()
{
	m_gameStates.back()->onEnter();
}

void GameStateMachine::update()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->update();
	}
}

void GameStateMachine::render()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->render();
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
