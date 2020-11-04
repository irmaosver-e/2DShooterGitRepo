#ifndef __GameOverState__
#define __GameOverState__

#include "MenuState.h"

class GameOverState : public MenuState
{
public:
	virtual bool onEnter();

	virtual std::string getStateID() const { return s_gameOverID; }

private:
	static const std::string s_gameOverID;

	//call back functions for menu items
	static void s_gameOverToMain();
	static void s_restartPlay();
};

#endif /* defined ( __GameOverState__ ) */