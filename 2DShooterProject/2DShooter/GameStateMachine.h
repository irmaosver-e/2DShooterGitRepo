#ifndef __GameStateMachine__
#define __GameStateMachine__

#include <vector>
#include "Singleton.h"
#include "GameState.h"

enum States {MAIN, PLAY, PAUSE, GAME_OVER, NEXT_LEVEL};

class GameStateMachine : public Singleton<GameStateMachine>
{
public:
	GameStateMachine(token) :
		m_pCurrentState(nullptr),
		m_pPreviousState(nullptr),
		m_bQuitStates(false),
		m_bChangingState(false),
		m_numberOfStages(0),
		m_stageNumber(1){}

	~GameStateMachine() {}

	void init();

	void changeState(States state);
	void pushState(States state);
	void popState();

	void update();
	void render();
	void quit();
	void clean();

	bool getQuitStates() { return m_bQuitStates; }

	//redundant
	//std::vector<GameState*>& getGameStates() { return m_gameStates; }

private:
	void manageNextPlayState(States& state);

	GameState* createState(States& state);
	std::string getStateID(States& state);

	std::vector<GameState*> m_menuStates;
	std::vector<GameState*> m_playStates;
	GameState* m_pCurrentState;
	GameState* m_pPreviousState;
	bool m_bChangingState;
	bool m_bQuitStates;

	//in progress
	int m_numberOfStages;
	int m_stageNumber;

};

typedef GameStateMachine TheGameStateMachine;

#endif /* defined ( __GameStateMachine__ ) */
