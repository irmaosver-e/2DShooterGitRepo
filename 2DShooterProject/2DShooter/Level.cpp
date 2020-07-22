#include "Level.h"

#include "Game.h"
#include "ObjectLayer.h"


Level::~Level()
{
	for (unsigned int i = 0; i < m_layers.size(); i++)
	{
		delete m_layers[i];
	}

	m_layers.clear();
}

void Level::update()
{
	for (unsigned int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->update(this);
	}
}

void Level::render()
{
	for (unsigned int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->render();
	}
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
