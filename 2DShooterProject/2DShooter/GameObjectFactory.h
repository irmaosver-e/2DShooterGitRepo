#ifndef __GameObjectFactory__
#define __GameObjectFactory__

#include <string>
#include <map>
#include "BaseCreator.h"
#include "GameObject.h"

class GameObjectFactory
{
public:
	static GameObjectFactory* Instance();

	bool registerType(std::string typeID, BaseCreator* pCreator);
	GameObject* create(std::string typeID);

private:
	GameObjectFactory() {}
	~GameObjectFactory() {}

	static GameObjectFactory* s_pInstance; //the singleton instance

	std::map<std::string, BaseCreator*> m_creators;
};

typedef GameObjectFactory TheGameObjectFactory;

#endif /* defined ( __GameObjectFactory__ ) */