#ifndef __MainMenuState__
#define __MainMenuState__

#include <iostream>

#include "MenuState.h"
#include "GameObject.h"

class MainMenuState : public MenuState
{
public:
	virtual ~MainMenuState() { delete m_pLevel; }

	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_menuID; }

private:
	static const std::string s_menuID;

	//virtual void setCallbacks(const std::vector<Callback>& callbacks);

	//call back functions for menu items
	static void s_menuToPlay();
	static void s_exitFromMenu();
};

#endif /* defined ( __MainMenuState__ ) */
