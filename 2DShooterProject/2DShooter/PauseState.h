#ifndef __PauseState__
#define __PauseState__

#include <iostream>

#include "MenuState.h"
#include "GameObject.h"

#include "InputHandler.h"
#include "TextureManager.h"
#include "Game.h"
#include "StateParser.h"

#include "MenuButton.h"
#include "MainMenuState.h"

class PauseState : public MenuState
{
public:
	virtual ~PauseState() {}

	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_pauseID; }

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:
	static const std::string s_pauseID;

	//std::vector<GameObject*> m_gameObjects;

	//call back functions for menu items
	static void s_pauseToMain();
	static void s_resumePlay();
};

#endif /* defined ( __PauseState__ ) */
