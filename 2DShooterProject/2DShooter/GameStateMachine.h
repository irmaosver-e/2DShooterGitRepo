#ifndef __GameStateMachine__
#define __GameStateMachine__

#include <vector>
#include "GameState.h"

class GameStateMachine
{
public:
	GameStateMachine() {}
	~GameStateMachine() {}

	void changeState(GameState* pState);
	void pushState(GameState* pState);
	void popState();

	void update();
	void render();
	void clean();

	std::vector<GameState*>& getGameStates() { return m_gameStates; }
private:
	std::vector<GameState*> m_gameStates;
};

#endif /* defined ( __GameStateMachine__ ) */
