#ifndef __EndingState__
#define __EndingState__

#include "MenuState.h"

class EndingState : public MenuState
{
public:
	virtual bool onEnter();

	virtual std::string getStateID() const { return s_endingID; }

private:
	static const std::string s_endingID;

	//call back functions for menu items
	static void s_gameOverToMain();

};

#endif /* defined ( __EndingState__ ) */