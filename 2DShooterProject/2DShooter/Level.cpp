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
		pLayer->update(this);
	}
}

void Level::render()
{
	for (Layer* pLayer : m_layers)
	{
		pLayer->render();
	}
}

TileLayer* Level::getTileLayerByName(std::string tileLayer)
{
	for (int i = 0; i < m_tileLayers.size(); i++)
	{
		if(m_tileLayers[i]->refLayerName() == tileLayer)
		{
			return m_tileLayers[i];
		}
	}
	return nullptr;
}

ObjectLayer* Level::getObjectLayerByName(std::string objLayer)
{
	for (int i = 0; i < m_tileLayers.size(); i++)
	{
		if (m_objectLayers[i]->refLayerName() == objLayer)
		{
			return m_objectLayers[i];
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
				if (objType == (*itObject)->getTextureID() || objType == "all")
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
