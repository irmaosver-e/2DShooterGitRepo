#ifndef __Game__
#define __Game__

#include <SDL.h>
#include <vector>
#include <iostream>

#include "GameStateMachine.h"

class Game
{
public:
	static Game* Instance();

	//set the running variable to true
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen);
	void render();
	void update();
	void handleEvents();
	void clean();

	int getGameWidth() const { return m_gameWidth; }
	int getGameHeight() const { return m_gameHeight; }
	int getScrollSpeed() const { return m_scrollSpeed; }
	
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

	bool running() { return m_bRunning; }
	void quit() { m_bRunning = false; }

	SDL_Renderer* getRenderer() const{ return m_pRenderer; }
	SDL_Window* getWindow() const { return m_pWindow; }
	GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

private:
	Game();
	~Game();
	Game(const Game&);
	Game& operator=(const Game&);

	static Game* s_pInstance; //the singleton instance
	bool m_bRunning;

	SDL_Window* m_pWindow = 0;
	SDL_Renderer* m_pRenderer = 0;

	GameStateMachine* m_pGameStateMachine;
	bool m_bChangingState;

	int m_gameWidth;
	int m_gameHeight;
	float m_scrollSpeed;
	
	int m_playerLives;

	int m_currentLevel;
	int m_nextLevel;
	bool m_bLevelComplete;

	std::vector<std::string> m_levelFiles;

};

typedef Game TheGame;

#endif /* defined(__Game__)*/