#include "GameStateMachine.h"

#include <iostream>
#include "ParserManager.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "GameOverState.h"

void GameStateMachine::changeState(States state)
{
	m_bChangingState = true;

	if (!m_gameStates.empty())
	{
		// trying to change to same state - do nothing
		if (m_pCurrentState->getStateID() == getStateID(state))
		{
			std::cout << " in GameStateMachine::changeState - changing to same state as current \n";
			std::cout << "change state: " << getStateID(state) << "\n";
			return;
		}
	}

	popState();

	pushState(state);

	m_bChangingState = false;
}

void GameStateMachine::pushState(States state)
{
	// if only pushing the state store the previous state for poping
	if (!m_bChangingState && !m_gameStates.empty())
	{
		m_pPreviousState = m_pCurrentState;
	}

	//checks if the state already exists
	for (GameState* pGameState : m_gameStates)
	{

		if (pGameState->getStateID() == getStateID(state))
		{
			//the state exists already use it instead
			m_pCurrentState = pGameState;
			
			//probably not enter but restart needs checking!!!!!!!!!!!!!1
			m_pCurrentState->onEnter();
		
			return;
		}
	}

	//parse state if non existent
	GameState* pState = createState(state);
	TheParserManager::Instance().getStateParserRef().parseState(pState);

	m_gameStates.push_back(pState);

	m_pCurrentState = m_gameStates.back();

	m_pCurrentState->onEnter();
}

void GameStateMachine::popState()
{
	if (!m_gameStates.empty())
	{
		m_pCurrentState->onExit();

		if (m_bChangingState)
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

void GameStateMachine::quit()
{
	m_bQuitStates = true;
}

void GameStateMachine::clean()
{
	m_bChangingState = true;
	popState();

	m_pCurrentState = nullptr;

	for (GameState* state : m_gameStates)
	{
		delete state;
	}

	m_gameStates.clear();
}

GameState* GameStateMachine::createState(States& state)
{
	switch (state)
	{
	case MAIN:
		return new MainMenuState();
	case PLAY:
		return new PlayState();
	case PAUSE:
		return new PauseState();
	case GAME_OVER:
		return new GameOverState();
	}

	return nullptr;
}

std::string GameStateMachine::getStateID(States& state)
{
	switch (state)
	{
	case MAIN:
		return "MENU";
	case PLAY:
		return "PLAY";
	case PAUSE:
		return "PAUSE";
	case GAME_OVER:
		return "GAMEOVER";
	}

	return "NO_STATE_FOUND";
}
