#include "Level.h"

#include "Game.h"
#include "ObjectLayer.h"


Level::~Level()
{
	for (Layer* pLayer : m_layers)
	{
		delete pLayer;
	}

	m_layers.clear();
}

void Level::update()
{
	for (Layer* pLayer : m_layers)
	{
		pLayer->update();
	}
}

void Level::render()
{
	for (Layer* pLayer : m_layers)
	{
		pLayer->render();
	}
}

void Level::reset()
{
	for (ObjectLayer* pObjLayer : m_objectLayers)
	{
		pObjLayer->reset();
	}
}

TileLayer* Level::getTileLayerByName(std::string tileLayer)
{
	for (TileLayer* pTileLayer : m_tileLayers)
	{
		if(pTileLayer->getLayerNameRef() == tileLayer)
		{
			return pTileLayer;
		}
	}
	return nullptr;
}

ObjectLayer* Level::getObjectLayerByName(std::string objLayer)
{
	for (ObjectLayer* pObjectLayer : m_objectLayers)
	{
		if (pObjectLayer->getLayerNameRef() == objLayer)
		{
			return pObjectLayer;
		}
	}
	return nullptr;
}

void Level::getObjectsfromLayers(std::vector<GameObject*>& objContainer, std::string objType, std::string layer)
{
	if (layer == "all")
	{
		for(unsigned int i = 0; i < m_objectLayers.size(); i++)
		{
			for (std::vector<GameObject*>::iterator itObject = m_objectLayers[i]->getGameObjects()->begin();
				itObject != m_objectLayers[i]->getGameObjects()->end();
				++itObject)
			{
				if (objType == (*itObject)->getSubTypeID() || objType == "all")
				{
					objContainer.push_back(*itObject);
				}
			}
		}
	}
	else
	{
		//to be expanded
		//m_objectLayers.at(0);
	}
}
