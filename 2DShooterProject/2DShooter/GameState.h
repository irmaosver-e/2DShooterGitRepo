#ifndef __GameState__
#define __GameState__

#include <string>

#include "Level.h"


class GameState
{
public:
	virtual ~GameState() { delete m_pLevel; }
	virtual void init();

	virtual bool update();
	virtual bool render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual bool resume();

	virtual std::string getStateID() const = 0;

	Level* getLevel() { return m_pLevel; }
	//std::string& stageMapFileName() { return m_stageMapFile; }
	//std::string& stageAssetsPath() { return m_stageAssetsPath; }

protected:

	GameState() : m_loadingComplete(false), m_exiting(false){}
	
	Level* m_pLevel;
	
	//possibly redundant
	bool m_loadingComplete;
	bool m_exiting;

	//std::string m_stageAssetsPath;
	//std::string m_stageMapFile;

};

#endif /* defined ( __GameState__ ) */