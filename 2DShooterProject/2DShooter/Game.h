#ifndef __Game__
#define __Game__

class Game
{
public:
	Game();
	~Game() {}

	bool init(const char* configFile);
	void run();
	void clean();

	//const int getCurrentLevel() { return m_currentLevel; }
	//const int getNextLevel() { return m_nextLevel; }
	//const int getLevelComplete() { return m_bLevelComplete; }
	//std::map<int, std::string> getLevelFiles() { return m_levelFiles; }

	//void setCurrentLevel(int currentLevel);
	//void setNextLevel(int nextLevel) { m_nextLevel = nextLevel; }
	//void addLevelFile(int levelNumber, std::string filename);
	//void setLevelComplete(bool levelComplete) { m_bLevelComplete = levelComplete; }

	//void setAssetsRoot(std::string path) { m_assetsRoot = path; }
	//void setStatesFile(std::string filename) { m_statesFile = filename; }

	//std::string getAssetsRoot() { return m_assetsRoot; }
	//std::string getStatesFile() { return m_statesFile; }

	//bool getchangingStateFlag() { return m_bChangingState; }
	//void setChangingStateFlag(bool changingState) { m_bChangingState = changingState; }

	bool isRunning() { return m_bRunning; }


private:
	void render();
	void update();
	void handleEvents();

	void registerObjTypes();

	bool m_bRunning;

	//bool m_bChangingState;

	//int m_currentLevel;
	//int m_nextLevel;
	//bool m_bLevelComplete;

	//std::string m_assetsRoot;
	//std::string m_statesFile;
	//std::map<int, std::string> m_levelFiles;
	//std::map<int, std::string> m_tileSetFiles;

};

#endif /* defined(__Game__)*/