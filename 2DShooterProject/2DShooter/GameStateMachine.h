#ifndef __GameStateMachine__
#define __GameStateMachine__

#include <vector>
#include "Singleton.h"
#include "GameState.h"

enum States {MAIN, PLAY, PAUSE, GAME_OVER};

class GameStateMachine : public Singleton<GameStateMachine>
{
public:
	GameStateMachine(token) :
		m_pCurrentState(nullptr),
		m_pPreviousState(nullptr),
		m_bQuitStates(false),
		m_bChangingState(false) {}

	~GameStateMachine() {}

	void changeState(States state);
	void pushState(States state);
	void popState();
	void reloadState();

	void update();
	void render();
	void quit();
	void clean();

	bool getQuitStates() { return m_bQuitStates; }

	std::vector<GameState*>& getGameStates() { return m_gameStates; }

private:
	GameState* createState(States& state);
	std::string getStateID(States& state);

	std::vector<GameState*> m_gameStates;
	GameState* m_pCurrentState;
	GameState* m_pPreviousState;
	bool m_bChangingState;
	bool m_bQuitStates;
};

typedef GameStateMachine TheGameStateMachine;

#endif /* defined ( __GameStateMachine__ ) */
