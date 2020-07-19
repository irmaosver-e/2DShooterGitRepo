#include "Level.h"

//#include <math.h>
//#include "TextureManager.h"
#include "Game.h"
#include "Layer.h"
//#include "TileLayer.h"

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
	//check colisions here?
	//pass state from game singleton to collision manager?

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
		for (std::vector<ObjectLayer*>::iterator itObjLayers = m_objectLayers.begin();
			itObjLayers != m_objectLayers.end();
			++itObjLayers)
		{
			for (std::vector<GameObject*>::iterator itObject = (*itObjLayers)->getGameObjects()->begin();
				itObject != (*itObjLayers)->getGameObjects()->end();
				++itObject)
			{
				if (objType == (*itObject)->objType() || objType == "all")
				{
					objContainer.push_back(*itObject);
				}
			}
		}
	}
	else
	{
		//to be expanded
		m_objectLayers.at(0);
	}
}
