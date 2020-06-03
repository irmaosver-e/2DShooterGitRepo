#ifndef __Game__
#define __Game__

#include <vector>

#include "Singleton.h"
#include "GameStateMachine.h"

class Game : public Singleton<Game>
{
public:
	Game(token);
	~Game() {}

	//set the running variable to true
	bool init(const char* configFile);
	void run();
	void clean();

	float getScrollSpeed() const { return m_scrollSpeed; }
	
	int getPlayerLives() { return m_playerLives; }
	void setPlayerLives(int lives) { m_playerLives = lives; }

	const int getCurrentLevel() { return m_currentLevel; }
	const int getNextLevel() { return m_nextLevel; }
	const int getLevelComplete() { return m_bLevelComplete; }
	std::vector<std::string> getLevelFiles() { return m_levelFiles; }

	void setCurrentLevel(int currentLevel);
	void setNextLevel(int nextLevel) { m_nextLevel = nextLevel; }
	void setLevelComplete(bool levelComplete) { m_bLevelComplete = levelComplete; }

	bool getchangingStateFlag() { return m_bChangingState; }
	void setChangingStateFlag(bool changingState) { m_bChangingState = changingState; }

	bool isRunning() { return m_bRunning; }
	void quit() { m_bRunning = false; }

	GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

private:
	void render();
	void update();
	void handleEvents();

	bool m_bRunning;

	GameStateMachine* m_pGameStateMachine;
	bool m_bChangingState;

	float m_scrollSpeed;
	
	int m_playerLives;

	int m_currentLevel;
	int m_nextLevel;
	bool m_bLevelComplete;

	std::vector<std::string> m_levelFiles;

};

typedef Game TheGame;

#endif /* defined(__Game__)*/