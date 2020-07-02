#ifndef __GameState__
#define __GameState__

#include <string>
#include <vector>

#include "Level.h"

class GameObject;

class GameState
{
public:
	virtual ~GameState() {}

	virtual void update();
	virtual void render();
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	//virtual void resume() {}
	//std::vector<std::string>* getTextureIDList() { return &m_textureIDList; }
	//std::vector<GameObject*>* getGameObjects() { return &m_gameObjects; }

	virtual std::string getStateID() const = 0;

	void setStageMapFile(std::string file) { m_stageMapFile = file; }
	void setStageAssetsPath(std::string path) { m_stageAssetsPath = path; }

protected:

	GameState() : m_loadingComplete(false), m_exiting(false){}
	
	Level* m_pLevel;

	bool m_loadingComplete;
	bool m_exiting;

	//to b made redundant used when loading objects straight from states file
	std::vector<std::string> m_textureIDList;
	std::vector<GameObject*> m_gameObjects;
	// -----------------

	std::string m_stageAssetsPath;
	std::string m_stageMapFile;
};

#endif /* defined ( __GameState__ ) */