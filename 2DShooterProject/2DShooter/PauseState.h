#ifndef __PauseState__
#define __PauseState__

#include "MenuState.h"

class PauseState : public MenuState
{
public:
	virtual ~PauseState() { delete m_pLevel; }

	virtual bool onEnter();
	virtual bool onExit();

	virtual bool update();

	virtual std::string getStateID() const { return s_pauseID; }

private:
	static const std::string s_pauseID;

	//call back functions for menu items
	static void s_pauseToMain();
	static void s_resumePlay();
};

#endif /* defined ( __PauseState__ ) */
