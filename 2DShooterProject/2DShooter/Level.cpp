#include "Level.h"

#include "SoundManager.h"
#include "ObjectLayer.h"
#include "BulletHandler.h"


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

void Level::resetLevel()
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

void Level::onEnter()
{
	TheSoundManager::Instance().playMusic(m_levelMusicID, m_loopMusic);
	
	if (m_bPlayLevel && !m_pPlayer)
	{
		//its a playLevel need to register the layer to the bulletHandler
		TheBulletHandler::Instance().registerBulletLayer(m_pBulletLayer);

		m_pPlayer = dynamic_cast<Player*>(m_pPlayerLayer->getGameObjects()->back());
	}
	if (m_pBulletLayer)
	{
		//its a playLevel need to register the layer to the bulletHandler
		TheBulletHandler::Instance().registerBulletLayer(m_pBulletLayer);
	}

	//for testing
	if (m_pPlayer)
	{
		std::cout << "Player test code in Level::onEnter()\n";
		//m_pPlayer->turnObjOn();
		//m_pPlayer->flyIntoScreen();

		//needed to spawn the player
		m_pPlayerLayer->resetMarkers();

		m_pPlayerLayer->turnObjectsOff();
	}
}

void Level::onExit()
{
	//TheSoundManager::Instance().stopMusic();
	resetLevel();
	m_pPlayer = nullptr;
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

void Level::setLevelMusic(std::string& musicID, int& loop)
{
	m_levelMusicID = musicID;
	m_loopMusic = loop;
}
