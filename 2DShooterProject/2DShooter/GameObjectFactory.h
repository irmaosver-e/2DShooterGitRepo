#ifndef __GameObjectFactory__
#define __GameObjectFactory__

#include <string>
#include <map>
#include "Singleton.h"
#include "BaseCreator.h"
#include "GameObject.h"

class GameObjectFactory : public Singleton<GameObjectFactory>
{
public:
	GameObjectFactory(token) {}
	~GameObjectFactory() {}

	bool registerType(std::string typeID, BaseCreator* pCreator);
	GameObject* create(std::string typeID);

	void clearCreators();

private:
	std::map<std::string, BaseCreator*> m_creators;
};

typedef GameObjectFactory TheGameObjectFactory;

#endif /* defined ( __GameObjectFactory__ ) */