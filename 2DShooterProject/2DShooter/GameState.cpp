#include "GameState.h"

void GameState::update()
{
	if (m_pLevel)
	{
		m_pLevel->update();
	}
}

void GameState::render()
{
	if (m_pLevel != 0)
	{
		m_pLevel->render();
	}
}
