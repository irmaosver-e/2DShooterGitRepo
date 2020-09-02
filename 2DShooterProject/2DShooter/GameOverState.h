#ifndef __GameOverState__
#define __GameOverState__

#include <vector>

#include "MenuState.h"

class GameObject;

class GameOverState : public MenuState
{
public:
	virtual ~GameOverState() {}

	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_gameOverID; }

	//virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:
	static const std::string s_gameOverID;

	//std::vector<GameObject*> m_gameObjects;

	//call back functions for menu items
	static void s_gameOverToMain();
	static void s_restartPlay();
};

#endif /* defined ( __GameOverState__ ) */