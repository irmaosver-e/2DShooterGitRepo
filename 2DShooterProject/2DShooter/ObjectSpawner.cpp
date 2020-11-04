#include "ObjectSpawner.h"
#include "GameObjectFactory.h"
#include "SDLSystem.h"

void ObjectSpawner::spawnObject(ObjectLayer& objLayer, ObjectMarker& objMarker)
{
	if (objMarker.isActive)
	{
		//checks if objMarker  is in view
		if (objMarker.objPositionMarker.getX() < TheSDLSystem::Instance().getScreenWidth() && objMarker.objPositionMarker.getX() > 0 &&
			objMarker.objPositionMarker.getY() < TheSDLSystem::Instance().getScreenHeight() && objMarker.objPositionMarker.getY() > 0)
		{
			if (objMarker.objSubType == "bossPlane")
			{
				std::cout << "boss comming!";
			}

			int availableObjIndex = -1;

			for (unsigned int i = 0; i < objLayer.getGameObjects()->size(); i++)
			{
				//checks if object is available
				if (!objLayer.getGameObjects()->at(i)->isOn())
				{
					//test if the object available is of same type requested
					if (objLayer.getGameObjects()->at(i)->objType() == objMarker.objectType &&
						objLayer.getGameObjects()->at(i)->getSubTypeID() == objMarker.objSubType)
					{
						availableObjIndex = i;
					}
				}
			}

			//no obj in pool add obj
			if (availableObjIndex < 0)
			{
				
				objLayer.getGameObjectsRef().push_back(TheGameObjectFactory::Instance().create(objMarker.objectType));
				objLayer.getGameObjectsRef().back()->load(m_objParams[objMarker.objSubType]);

				availableObjIndex += objLayer.getGameObjects()->size();

				//for debugging
				//std::cout << "object added: " << objMarker.objectType <<"/ pool size " << availableObjIndex << "\n";
			}

			if(objLayer.getGameObjectsRef().at(availableObjIndex)->getSubTypeID() != objMarker.objSubType)
			{
				objLayer.getGameObjectsRef().at(availableObjIndex)->load(m_objParams[objMarker.objSubType]);
			}

			objLayer.getGameObjectsRef().at(availableObjIndex)->turnObjOn();
			objLayer.getGameObjectsRef().at(availableObjIndex)->setUpdating(true);
			objLayer.getGameObjectsRef().at(availableObjIndex)->setInView(true);
			objLayer.getGameObjectsRef().at(availableObjIndex)->reset(m_objParams[objMarker.objSubType]);

			objLayer.getGameObjectsRef().at(availableObjIndex)->getPosition() = objMarker.objPositionMarker;

			//for debugguing
			//std::cout << "object in pool: " << objLayer.getGameObjects()->size() << " / using object: " << availableObjIndex << " / type asked: " << objMarker.objectType << " / type used: " << objLayer.getGameObjects()->at(availableObjIndex)->getTextureID() << "\n";
			
			objMarker.isActive = false;
		}
	}

}

void ObjectSpawner::registerObjParams(std::string& objSubType, LoaderParams& params)
{
	//checks if the subtype already exist to avoid duplicate
	std::map<std::string, LoaderParams>::iterator itParam = m_objParams.find(objSubType);

	if (itParam == m_objParams.end())
	{
		m_objParams[objSubType] = params;
	}
}

bool ObjectSpawner::checkObjParamsMap(std::string& objSubType)
{
	//checks if the subtype exist
	std::map<std::string, LoaderParams>::iterator itParam = m_objParams.find(objSubType);

	if (itParam != m_objParams.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}
