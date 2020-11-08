#include "PlayState.h"

#include <iostream>
#include "GameStateMachine.h"
#include "SoundManager.h"
#include "InputHandler.h"

#include "Level.h"

const std::string PlayState::s_playID = "PLAY";

bool PlayState::update()
{
	if (GameState::update())
	{
		if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
		{
			//TheSoundManager::Instance().playSound("pause", 0);
			TheGameStateMachine::Instance().pushState(PAUSE);
		}

		if (m_pLevel->getPlayer()->outOfLives())
		{
			TheGameStateMachine::Instance().changeState(GAME_OVER);
		}

		if (m_pLevel->IsLevelComplete())
		{
			TheGameStateMachine::Instance().changeState(NEXT_LEVEL);
		}
		return true;
	}

	return false;
}

bool PlayState::render()
{
	if (GameState::render())
	{
		return true;
	}

	return false;
}

bool PlayState::onEnter()
{
	if (m_pLevel)
	{
		m_pLevel->setAsPlayLevel();

		GameState::onEnter();

		m_loadingComplete = true;

		return true;
	}

	return false;
}

bool PlayState::onExit()
{
	GameState::onExit();

	return true;
}