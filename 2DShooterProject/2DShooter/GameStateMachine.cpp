#include "GameStateMachine.h"

#include <iostream>
#include "ParserManager.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "GameOverState.h"

void GameStateMachine::init()
{
	m_numberOfStages = TheParserManager::Instance().getStateParserRef().countPlayStates();
	
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
		m_pCurrentState->init();
	}

	changeState(MAIN);
}

void GameStateMachine::changeState(States state)
{
	//test  code
	if (state == NEXT_LEVEL)
	{
		manageNextPlayState(state);
	}

	m_bChangingState = true;

	/* redundant check
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
	*/

	popState();

	pushState(state);

	m_bChangingState = false;
}

void GameStateMachine::pushState(States state)
{
	//store the previous state if only pushing for poping 
	//or changing to new level for player transfer
	if (!m_bChangingState)
	{
		m_pPreviousState = m_pCurrentState;
	}

	if (state == PLAY)
	{
		m_pCurrentState = m_playStates[m_stageNumber - 1];
	}
	else
	{
		for (GameState* pGameState : m_menuStates)
		{
			if (pGameState->getStateID() == getStateID(state))
			{
				//the state exists already use it instead
				m_pCurrentState = pGameState;

				break;
			}
		}
	}

	//probably not enter but restart needs checking!!!!!!!!!!!!!1
	m_pCurrentState->onEnter();

	return;
}

void GameStateMachine::popState()
{
	m_pCurrentState->onExit();

	if (m_bChangingState)
	{
		if (m_pPreviousState)
		{
			//transfer player to first play stage
			m_playStates[0]->getLevel()->getPlayerLayerPtr()->addObjectToLayer(m_pPreviousState->getLevel()->getPlayerLayerPtr()->getGameObjects()->back());

			//removes the player from the old state level
			m_pPreviousState->getLevel()->getPlayerLayerPtr()->getGameObjects()->pop_back();

			//going back to MENU from PAUSE
			m_pPreviousState->onExit();
			m_stageNumber = 1;
		}
	}
	else
	{
		// returning from PAUSE
		m_pCurrentState = m_pPreviousState;
		m_pCurrentState->resume();
	}

	m_pPreviousState = nullptr;
}


void GameStateMachine::manageNextPlayState(States& state)
{
	//finds the next stage number as index of m_playstates
	int nextStage = 0;
	for (int playStatesIndex = 0; playStatesIndex < m_playStates.size(); playStatesIndex++)
	{
		if (m_pCurrentState == m_playStates[playStatesIndex])
		{
			nextStage = playStatesIndex + 2;
			m_stageNumber = playStatesIndex + 2;
			break;
		}
	}

	if (nextStage > m_playStates.size())
	{
		if (m_playStates.size() < m_numberOfStages)
		{
			//create a new stage and set the play state to the new stage

			state = PLAY;
			GameState* pState = createState(state);

			TheParserManager::Instance().getStateParserRef().parseState(pState, nextStage);
			pState->init();

			//copy player Layer Markers
			pState->getLevel()->getPlayerLayerPtr()->getObjMarkersRef() = m_pCurrentState->getLevel()->getPlayerLayerPtr()->getObjMarkersRef();

			m_playStates.push_back(pState);
		}
		else
		{
			//end of game transfer the play state back to the first stage
			m_stageNumber = 1;
			state = GAME_OVER;
		}
	}
	//transfer player to new playstate
	m_playStates[m_stageNumber - 1]->getLevel()->getPlayerLayerPtr()->addObjectToLayer(m_pCurrentState->getLevel()->getPlayerLayerPtr()->getGameObjects()->back());

	//removes the player from the old state level
	m_pCurrentState->getLevel()->getPlayerLayerPtr()->getGameObjects()->pop_back();

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
	}

	return "NO_STATE_FOUND";
}
