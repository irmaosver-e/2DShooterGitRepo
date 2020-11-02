#include "PlayState.h"

#include <iostream>
#include "GameStateMachine.h"
#include "SoundManager.h"
#include "InputHandler.h"

#include "PauseState.h"
#include "GameOverState.h"
#include "Level.h"


const std::string PlayState::s_playID = "PLAY";

bool PlayState::update()
{
	if (GameState::update())
	{
		if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
		{
			//TheSoundManager::Instance().playSound("pause", 0);
			TheGameStateMachine::Instance().pushState(new PauseState());
		}

		if (m_pLevel->getPlayer()->outOfLives())
		{
			TheGameStateMachine::Instance().changeState(new GameOverState());
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
	std::cout << "PlayState::onEnter() \n";

	GameState::onEnter();

	if (m_pLevel)
	{
		m_loadingComplete = true;
	}

	return true;
}

bool PlayState::onExit()
{
	GameState::onExit();

	return true;
}