#include "GameOverState.h"

#include "Game.h"
#include "MainMenuState.h"
#include "PlayState.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

bool GameOverState::onEnter()
{
	GameState::onEnter();

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_gameOverToMain);
	m_callbacks.push_back(s_restartPlay);

	// set the callbacks for menu items
	setCallbacks(m_callbacks);

	m_loadingComplete = true;

	std::cout << "entering GameOverState\n";
	return true;
}

void GameOverState::s_gameOverToMain()
{
	TheGame::Instance().getStateMachine()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay()
{
	TheGame::Instance().getStateMachine()->changeState(new PlayState());
}



