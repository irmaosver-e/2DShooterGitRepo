#include "LevelParser.h"

#include <string>
#include "TextureManager.h"
#include "Game.h"
#include "ObjectLayer.h"
#include "TileLayer.h"
#include "GameObjectFactory.h"
#include "base64.h"
#include "zlib.h"
#include "Level.h"

Level* LevelParser::parseLevel(const char* levelFile)
{
	//create a TinyXML document and load the map XML
	TiXmlDocument levelDocument;
	levelDocument.LoadFile(levelFile);

	// create the level object
	Level* pLevel = new Level();

	//get the root node
	TiXmlElement* pRoot = levelDocument.RootElement();

	pRoot->Attribute("tilewidth", &m_tileSize);
	pRoot->Attribute("width", &m_width);
	pRoot->Attribute("height", &m_height);

	//we know that properties is the first child of the root
	//TiXmlElement* pProperties = pRoot->FirstChildElement();

	TiXmlElement* pProperties = NULL;
	std::vector<TiXmlElement*> pTilesetElements;
	std::vector<TiXmlElement*> pLayerElements;

	//parse textures added to property
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("properties"))
		{
			pProperties = e;
		}

		if (e->Value() == std::string("tileset"))
		{
			pTilesetElements.push_back(e);
		}

		if (e->Value() == std::string("layer") || e->Value() == std::string("objectgroup"))
		{
			pLayerElements.push_back(e);
		}
	}

	//parse textures added to properties
	for (TiXmlElement* e = pProperties->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("property"))
		{
			if (e->Attribute("name") == std::string("assetsPath"))
			{
				m_assetsLocation = e->Attribute("value");
			}
			else
			{
				parseTextures((m_assetsLocation + e->Attribute("value")), e->Attribute("name"));
			}
		}
	}

	//parse the tileset
	for (unsigned int i = 0; i < pTilesetElements.size(); i++ )
	{
		parseTilesets(pTilesetElements[i], pLevel->getTilesets());
	}

	//parse any Layer
	for (unsigned int i = 0; i < pLayerElements.size(); i++)
	{
		TiXmlNode* firstChild = pLayerElements[i]->FirstChildElement();
		TiXmlNode* nextChild = firstChild->NextSiblingElement();

		if (firstChild->Value() == std::string("object"))
		{
			parseObjectLayer(pLayerElements[i], pLevel->getLayers(), pLevel);
		}
		else if (firstChild->Value() == std::string("data") || (nextChild != 0 && nextChild->Value() == std::string("data")))
		{
			parseTileLayer(pLayerElements[i], pLevel->getLayers(), pLevel->getTilesets(), pLevel->getCollisionLayers());
		}

	}

	return pLevel;
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
	//add tileset to textureManager
	parseTextures((m_assetsLocation + pTilesetRoot->FirstChildElement()->Attribute("source")), 
					pTilesetRoot->Attribute("name"));
	
	//create a tileset object
	Tileset tileset;
	pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
	pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);

	pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
	pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
	pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
	pTilesetRoot->Attribute("spacing", &tileset.spacing);
	pTilesetRoot->Attribute("margin", &tileset.margin);

	tileset.name = pTilesetRoot->Attribute("name");

	tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

	pTilesets->push_back(tileset);
}

void LevelParser::parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets, std::vector<TileLayer*> *pCollisionLayers)
{
	TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);

	bool collidable = false;

	//tile data
	std::vector<std::vector<int>> data;

	std::string decodedIDs;
	TiXmlElement* pDataNode = NULL;

	for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("properties"))
		{
			for (TiXmlElement* property = e->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
			{
				if (property->Value() == std::string("property"))
				{
					if (property->Attribute("name") == std::string("collidable"))
					{
						collidable = true;
					}
				}
			}
		}

		if (e->Value() == std::string("data"))
		{
			pDataNode = e;
		}
	}


	for (TiXmlNode* n = pDataNode->FirstChild(); n != NULL; n = n->NextSibling())
	{
		TiXmlText* text = n->ToText();
		std::string t = text->Value();
		decodedIDs = base64_decode(t);
	}

	//decompress zlib compression
	uLongf numGids = m_width * m_height * sizeof(int);
	std::vector<unsigned> gids(numGids);
	uncompress((Bytef*)&gids[0], &numGids, (const Bytef*)decodedIDs.c_str(), (uLong)decodedIDs.size());

	std::vector<int> layerRow(m_width);

	for (int j = 0; j < m_height; j++)
	{
		data.push_back(layerRow);
	}

	for (int rows = 0; rows < m_height; rows++)
	{
		for (int cols = 0; cols < m_width; cols++)
		{
			data[rows][cols] = gids[(rows * m_width) + cols];
		}
	}
	pTileLayer->setTileIDs(data);
	pTileLayer->setMapWidth(m_width);

	if (collidable)
	{
		pCollisionLayers->push_back(pTileLayer);
	}

	pLayers->push_back(pTileLayer);
}

bool LevelParser::parseTextures(std::string fileName, std::string id)
{
	if (!TheTextureManager::Instance().load(fileName, id, TheGame::Instance().getRenderer()))
	{
		std::cout << "failed to load texture in LevelParser::parseTextures \n";
		return false;
	}
	return true;
}

void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*> *pLayers, Level* pLevel)
{
	ObjectLayer* pObjectLayer = new ObjectLayer();

	for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("object"))
		{
			int x = 0, y = 0, width = 0, height = 0, numFrames = 1, callbackID = 0, animSpeed = 1;
			std::string textureID;
			std::string type;

			//get the initial node values type, x and y
			e->Attribute("x", &x);
			e->Attribute("y", &y);

			type = e->Attribute("type");
			GameObject* pGameObject = TheGameObjectFactory::Instance().create(type);

			//get theProperty values
			for (TiXmlElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
			{
				if (properties->Value() == std::string("properties"))
				{
					for (TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
					{
						if (property->Value() == std::string("property"))
						{
							if (property->Attribute("name") == std::string("numFrames"))
							{
								property->Attribute("value", &numFrames);
							}
							else if (property->Attribute("name") == std::string("animSpeed"))
							{
								property->Attribute("value", &animSpeed);
							}
							else if (property->Attribute("name") == std::string("textureHeight"))
							{
								property->Attribute("value", &height);
							}
							else if (property->Attribute("name") == std::string("textureWidth"))
							{
								property->Attribute("value", &width);
							}
							else if (property->Attribute("name") == std::string("callbackID"))
							{
								property->Attribute("value", &callbackID);
							}
							else if (property->Attribute("name") == std::string("textureID"))
							{
								textureID = property->Attribute("value");
							}
						}
					}
				}
			}

			pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed)));
			
			if (type == "Player")
			{
				pLevel->setPlayer(dynamic_cast<Player*>(pGameObject));
			}

			pObjectLayer->getGameObjects()->push_back(pGameObject);
		}
	}
	pLayers->push_back(pObjectLayer);
}
