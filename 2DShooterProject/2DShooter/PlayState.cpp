#include "PlayState.h"

#include <iostream>
#include "SDLSystem.h"
#include "Game.h"
#include "SoundManager.h"
#include "BulletHandler.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "LevelParser.h"
#include "Level.h"

#include "TextureManager.h"


const std::string PlayState::s_playID = "PLAY";

bool PlayState::update()
{
	if (GameState::update())
	{
		if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
		{
			//TheSoundManager::Instance().playSound("pause", 0);
			TheGame::Instance().getStateMachine()->pushState(new PauseState());
		}

		//TheBulletHandler::Instance().updateBullets();

		if (m_pLevel->getPlayer()->outOfLives())
		{
			TheGame::Instance().getStateMachine()->changeState(new GameOverState());
		}

		return true;
	}

	return false;
}

bool PlayState::render()
{
	if (GameState::render())
	{
		for (int i = 0; i < m_pLevel->getPlayer()->checkLives(); i++)
		{
			TheTextureManager::Instance().drawTile("lives", 2, 2, i * 30, 0, 32, 32, 0, 0, TheSDLSystem::Instance().getRenderer());
		}

		//TheBulletHandler::Instance().drawBullets();

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