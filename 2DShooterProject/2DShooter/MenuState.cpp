#include "MenuState.h"

#include "MenuButton.h"


/*
void MenuState::update()
{
	if (m_loadingComplete && !m_exiting)
	{
		GameState::update();
	}
}

void MenuState::render()
{
	if (m_loadingComplete)
	{
		GameState::render();
	}
}

*/

void MenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
	std::vector<GameObject*> pObjectsContainer;
	m_pLevel->getObjectsfromLayers(pObjectsContainer);

	//go through the game objects
	if (!pObjectsContainer.empty())
	{
		for (unsigned int i = 0; i < pObjectsContainer.size(); i++)
		{
			// if they are of type menu button assign callbacks based on IDs
			if (dynamic_cast<MenuButton*>(pObjectsContainer[i]))
			{
				MenuButton* pButton = dynamic_cast<MenuButton*>(pObjectsContainer[i]);
				pButton->setCallback(callbacks[pButton->getCallbackID()]);
			}
		}
	}
}
