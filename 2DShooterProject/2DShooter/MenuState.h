#ifndef __MenuState__
#define __MenuState__

#include "GameState.h"

#include "MenuButton.h"

class MenuState : public GameState
{
public:
	virtual ~MenuState() {}

protected:
	typedef void(*Callback)();
	virtual void setCallbacks(const std::vector<Callback>& callbacks)
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

		//pObjectsContainer.clear();
	}

	std::vector<Callback> m_callbacks;

};

#endif /* defined ( __MenuState__ ) */
