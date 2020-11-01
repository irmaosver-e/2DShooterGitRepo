#ifndef __GameStateMachine__
#define __GameStateMachine__

#include <vector>
#include "GameState.h"

class GameStateMachine
{
public:
	GameStateMachine() : 
		m_pCurrentState(nullptr),
		m_changingState(false){}

	~GameStateMachine() {}

	void changeState(GameState* pState);
	void pushState(GameState* pState);
	void popState();
	void reloadState();

	void update();
	void render();
	void clean();

	std::vector<GameState*>& getGameStates() { return m_gameStates; }

private:
	std::vector<GameState*> m_gameStates;
	std::vector<GameState*> m_previousStates;
	GameState* m_pCurrentState;
	bool m_changingState;
};

#endif /* defined ( __GameStateMachine__ ) */
