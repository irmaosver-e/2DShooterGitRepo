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

	if (m_bPlayLevel)
	{
		//checks if the boss has been created yet
		if (!m_pLevelBoss)
		{
			for (ObjectLayer* pObjLayer : m_objectLayers)
			{
				if (pObjLayer->hasObjectEnteredLayer())
				{
					//if an object entered the layer it is the last object in the vector,
					//checks to see if it is the boss
					m_pLevelBoss = dynamic_cast<Level1Boss*>(pObjLayer->getGameObjectsRef().back());
				}
			}
		}
		else
		{
			if (m_pLevelBoss->dead())
			{
				m_pPlayer->flyOffScreen();
				
				if (!m_pPlayer->isInView())
				{
					m_bLevelComplete = true; 
				}
			}
		}
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
	m_bLevelComplete = false;

	for (ObjectLayer* pObjLayer : m_objectLayers)
	{
		pObjLayer->reset();
	}
	for (ImageLayer* pImgLayer : m_imageLayers)
	{
		pImgLayer->resetPosition();
	}
	for (TileLayer* pTileLayer : m_tileLayers)
	{
		pTileLayer->resetPosition();
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

ObjectLayer* Level::getObjectLayerByName(std::string& objLayer)
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
