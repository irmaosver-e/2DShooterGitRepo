#include "GameObjectFactory.h"

bool GameObjectFactory::registerType(std::string typeID, BaseCreator* pCreator)
{
	//type already created, do nothing
	if (m_creators.find(typeID) != m_creators.end())
	{
		delete pCreator;
		return false;
	}

	m_creators[typeID] = pCreator;

	return true;
}

GameObject* GameObjectFactory::create(std::string typeID)
{
	//type already created, do nothing
	if (m_creators.find(typeID) == m_creators.end())
	{
		std::cout << "type already created or could not find type: " << typeID << "\n";
		return nullptr;
	}

	BaseCreator* pCreator = m_creators[typeID];

	return pCreator->createGameObject();
}
void GameObjectFactory::clearCreators()
{
	for (std::map<std::string, BaseCreator*>::iterator it = m_creators.begin(); it != m_creators.end(); it++)
	{
		delete it->second;
		it->second = nullptr;
	}

	m_creators.clear();
}

