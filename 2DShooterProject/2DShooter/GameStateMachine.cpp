#include "GameStateMachine.h"

#include <iostream>
#include "ParserManager.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "GameOverState.h"

void GameStateMachine::init()
{
	for(int i = MAIN; i < NEXT_LEVEL; i++)
	{
		States state = static_cast<States>(i);
		GameState* pState = createState(state);
		TheParserManager::Instance().getStateParserRef().parseState(pState);

		if (state == PLAY)
		{
			m_playStates.push_back(pState);
			m_pCurrentState = m_playStates.back();
		}
		else
		{
			m_menuStates.push_back(pState);
			m_pCurrentState = m_menuStates.back();
		}

		//initialize all states for use
		m_pCurrentState->onEnter();
		m_pCurrentState->onExit();
	}

	changeState(MAIN);
}

void GameStateMachine::changeState(States state)
{
	m_bChangingState = true;


	if (m_pCurrentState)
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
	if (m_pCurrentState)
	{
		//store the previous state if only pushing for poping 
		//or changing to new level for player transfer
		if (!m_bChangingState || (state == NEXT_LEVEL))
		{
			m_pPreviousState = m_pCurrentState;
		}
	}

	if (state == PLAY || state == NEXT_LEVEL)
	{
		for (GameState* pGameState : m_playStates)
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
	}
	else
	{
		for (GameState* pGameState : m_menuStates)
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
	}
	
	//parse state if non existent
	GameState* pState = createState(state);
	TheParserManager::Instance().getStateParserRef().parseState(pState);

	if (state == PLAY || state == NEXT_LEVEL)
	{
		m_playStates.push_back(pState);
		m_pCurrentState = m_playStates.back();
	}
	else
	{
		m_menuStates.push_back(pState);
		m_pCurrentState = m_menuStates.back();
	}

	//m_gameStates.push_back(pState);

	//m_pCurrentState = m_gameStates.back();

	m_pCurrentState->onEnter();
}

void GameStateMachine::popState()
{
	if (m_pCurrentState)
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
	if (m_pCurrentState)
	{
		m_pCurrentState->update();
	}
}

void GameStateMachine::render()
{
	if (m_pCurrentState)
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

	for (GameState* menuState : m_menuStates)
	{
		delete menuState;
	}
	for (GameState* playState : m_playStates)
	{
		delete playState;
	}

	m_menuStates.clear();
	m_playStates.clear();
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
	case NEXT_LEVEL:
		return "NEXT_LEVEL";
	}

	return "NO_STATE_FOUND";
}
