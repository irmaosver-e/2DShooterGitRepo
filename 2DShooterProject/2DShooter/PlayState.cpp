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


const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	if (m_loadingComplete && !m_exiting)
	{
		if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
		{
			TheGame::Instance().getStateMachine()->pushState(new PauseState());
		}

		TheBulletHandler::Instance().updateBullets();

		if (TheGame::Instance().getPlayerLives() == 0)
		{
			TheGame::Instance().getStateMachine()->changeState(new GameOverState());
		}

		if (pLevel)
		{
			pLevel->update();
		}
	}
}

void PlayState::render()
{
	if (m_loadingComplete)
	{
		if (pLevel != 0)
		{
			pLevel->render();
		}

		for (int i = 0; i < TheGame::Instance().getPlayerLives(); i++)
		{
			TheTextureManager::Instance().drawFrame("lives", i * 30, 0, 32, 30, 0, 0, TheSDLSystem::Instance().getRenderer(), 0.0, 255);
		}

		TheBulletHandler::Instance().drawBullets();
	}
}

bool PlayState::onEnter()
{
	TheGame::Instance().setPlayerLives(3);

	LevelParser levelParser;
	pLevel = levelParser.parseLevel((TheGame::Instance().getAssetsPath() + TheGame::Instance().getLevelFiles()[TheGame::Instance().getCurrentLevel()]).c_str());

	TheSoundManager::Instance().load("assets/boom.wav", "explode", SOUND_SFX);
	TheSoundManager::Instance().load("assets/phaser.wav", "shoot", SOUND_SFX);

	TheTextureManager::Instance().load("assets/bullet1.png", "bullet1", TheSDLSystem::Instance().getRenderer());
	TheTextureManager::Instance().load("assets/bullet2.png", "bullet2", TheSDLSystem::Instance().getRenderer());
	TheTextureManager::Instance().load("assets/bullet3.png", "bullet3", TheSDLSystem::Instance().getRenderer());
	TheTextureManager::Instance().load("assets/lives.png", "lives", TheSDLSystem::Instance().getRenderer());

	if (pLevel)
	{
		m_loadingComplete = true;
	}

	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit()
{
	m_exiting = true;

	TheInputHandler::Instance().reset();
	TheBulletHandler::Instance().clearBullets();

	std::cout << "exiting PlayState\n";
	return true;
}