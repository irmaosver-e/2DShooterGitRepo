#include "GameObjectFactory.h"

//Define static instance
GameObjectFactory* GameObjectFactory::s_pInstance = nullptr;

GameObjectFactory* GameObjectFactory::Instance()
{
	if (!s_pInstance)
	{
		s_pInstance = new GameObjectFactory();
	}
	return s_pInstance;
}

bool GameObjectFactory::registerType(std::string typeID, BaseCreator* pCreator)
{
	std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

	//type already created, do nothing
	if (it != m_creators.end())
	{
		delete pCreator;
		return false;
	}

	m_creators[typeID] = pCreator;

	return true;
}

GameObject* GameObjectFactory::create(std::string typeID)
{
	std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

	//type already created, do nothing
	if (it == m_creators.end())
	{
		std::cout << "could not find type: " << typeID << "\n";
		return nullptr;
	}

	BaseCreator* pCreator = (*it).second;

	return pCreator->createGameObject();
} 
