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

	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	//virtual void resume() {}

	virtual std::string getStateID() const = 0;
	std::vector<std::string>* getTextureIDList() { return &m_textureIDList; }
	std::vector<GameObject*>* getGameObjects() { return &m_gameObjects; }

	void setStageMapFile(std::string file) { m_stageMapFile = file; }
	void setStageAssetsPath(std::string path) { m_stageAssetsPath = path; }

protected:

	GameState() : m_loadingComplete(false), m_exiting(false){}
	
	Level* m_pLevel;

	bool m_loadingComplete;
	bool m_exiting;

	std::vector<std::string> m_textureIDList;
	std::vector<GameObject*> m_gameObjects;

	std::string m_stageAssetsPath;
	std::string m_stageMapFile;
};

#endif /* defined ( __GameState__ ) */