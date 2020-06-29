#include "LevelParser.h"

#include <string>
#include "SDLSystem.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "ObjectLayer.h"
#include "TileLayer.h"
#include "GameObjectFactory.h"
#include "base64.h"
#include "zlib.h"
#include "Level.h"

#include "Tileset.h" 
/* To be made redundant
Level* LevelParser::parseLevel(std::string assetsLocation, std::string levelFile)
{
	//create a TinyXML document and load the map XML
	TiXmlDocument levelDocument;
	levelDocument.LoadFile(assetsLocation + levelFile);

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

	//parse the object textures
	for (TiXmlElement* e = pProperties->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("property"))
		{
			parseTextures((assetsLocation + e->Attribute("value")), e->Attribute("name"));
		}
	}

	//parse the tileset
	for (unsigned int i = 0; i < pTilesetElements.size(); i++ )
	{
		parseTilesets(pTilesetElements[i], pLevel->getTilesets(), assetsLocation);
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
*/
/* to be made redundant
void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets, std::string assetsLocation)
{

	//add tileset to textureManager
	parseTextures((assetsLocation + pTilesetRoot->FirstChildElement()->Attribute("source")), 
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
*/
Level* LevelParser::parseLevel(std::string assetsLocation, std::string levelFile)
{
	m_pLevel = new Level(assetsLocation, levelFile);

	TiXmlDocument xmlDoc;

	TiXmlElement* pRoot = loadDocument(xmlDoc, assetsLocation, levelFile);

	pRoot->Attribute("tilewidth", &m_mapTileWidth);
	pRoot->Attribute("tileheight", &m_mapTileHeight);
	pRoot->Attribute("width", &m_mapNumColumns);
	pRoot->Attribute("height", &m_mapNumRows);

	TiXmlElement* pProperties = NULL;
	std::vector<TiXmlElement*> pLayerElements;

	//parse textures added to property
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("properties"))
		{
			int loop = 0;
			if (e->FirstChildElement()->Attribute("value") == std::string("loop"))
			{
				loop = -1;
			}

			TheSoundManager::Instance().playMusic(e->FirstChildElement()->Attribute("name"), loop);
		}
		else if (e->Value() == std::string("tileset"))
		{
			parseTileset(e);
		}
		else if (e->Value() == std::string("group") ||
			e->Value() == std::string("objectgroup") ||
			e->Value() == std::string("layer") ||
			e->Value() == std::string("imagelayer"))
		{
			parseLayer(e);
		}
		else
		{
			std::cout << "invalid value: " << e->Value() << " in" << levelFile << "\n";
		}
	}

	return m_pLevel;
}

void LevelParser::parseTileset(TiXmlElement* pTilesetElement)
{
	//create XML doc
	TiXmlDocument tilesetDoc;

	TiXmlElement* pTilesetRoot = loadDocument(tilesetDoc, m_pLevel->getlevelAssetsLocation(), pTilesetElement->Attribute("source"));

	//create a tileset object
	Tileset tileset;

	pTilesetElement->Attribute("firstgid", &tileset.firstGridID);
	pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
	pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
	pTilesetRoot->Attribute("columns", &tileset.numColumns);
	pTilesetRoot->Attribute("tilecount", &tileset.tileCount);
	tileset.name = pTilesetRoot->Attribute("name");

	if (!pTilesetRoot->Attribute("spacing", &tileset.spacing))
	{
		tileset.spacing = 0;
	}
	if (!pTilesetRoot->Attribute("margin", &tileset.margin))
	{
		tileset.margin = 0;
	}

	for (TiXmlElement* e = pTilesetRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("image"))
		{
			//add tileset to textureManager
			parseTextures((m_pLevel->getlevelAssetsLocation() + e->Attribute("source")), tileset.name);
			
			e->Attribute("width", &tileset.sourceWidth);
			e->Attribute("height", &tileset.sourceHeight);
		}
		else if (e->Value() == std::string("tile"))
		{
			ObjectTile objTile;
			parseObjTile(e, objTile);
			
			objTile.animation.sourceTileSet = tileset.name;
			objTile.animation.sourceColumns = tileset.numColumns;
			objTile.animation.sourceRows = tileset.tileCount / tileset.numColumns;

			tileset.objTileMap[objTile.type] = objTile;

			//register the animation with the textureManager
			TheTextureManager::Instance().getAnimationMap()[objTile.type] = objTile.animation;
		}
	}

	m_pLevel->getTilesets()->push_back(tileset);
}

void LevelParser::parseObjTile(TiXmlElement* pTileElement, ObjectTile& objectTile)
{
	objectTile.type = pTileElement->Attribute("type");
	
	for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("objectgroup"))
		{
			//parse the colision shape boxes
			for (TiXmlElement* object = e->FirstChildElement(); object != NULL; object = object->NextSiblingElement())
			{
				SDL_Rect collisionBox;

				object->Attribute("x", &collisionBox.x);
				object->Attribute("y", &collisionBox.y);
				object->Attribute("width", &collisionBox.w);
				object->Attribute("height", &collisionBox.h);

				objectTile.collisionShape.push_back(collisionBox);
			}
		}
		else if (e->Value() == std::string("animation"))
		{
			Animation objAnimation;
			
			e->FirstChildElement()->Attribute("duration", &objAnimation.frameDuration);

			for (TiXmlElement* frame = e->FirstChildElement(); frame != NULL; frame = frame->NextSiblingElement())
			{
				int frameID;
				frame->Attribute("tileid", &frameID);

				objAnimation.tileIDs.push_back(frameID);
			}
			objectTile.animation = objAnimation; 
		}
	}
}

void LevelParser::parseLayer(TiXmlElement* pLayerElement)
{	
	if (pLayerElement->Value() == std::string("group"))
	{
		for (TiXmlElement* e = pLayerElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
		{
			parseLayer(e);
		}
	}
	else if (pLayerElement->Value() == std::string("layer"))
	{
		parseTileLayer(pLayerElement);
	}
	else if (pLayerElement->Value() == std::string("imagelayer"))
	{
		parseImageLayer(pLayerElement);
	}
	else if (pLayerElement->Value() == std::string("objectgroup"))
	{
		parseObjectLayer(pLayerElement);
	}
	else
	{
		std::cout << "invalid layer Type: " << pLayerElement->Value() << " in level map \n";
	}
}

void LevelParser::parseTileLayer(TiXmlElement* pTileElement)
{
	TileLayer* pTileLayer = new TileLayer(*m_pLevel->getTilesets());

	//TileSize should be made redundant
	pTileLayer->setTileSize(m_mapTileWidth);
	
	pTileLayer->setTileWidth(m_mapTileWidth);
	pTileLayer->setTileHeight(m_mapTileHeight);
	pTileLayer->setNumColumns(m_mapNumColumns);
	pTileLayer->setNumRows(m_mapNumRows);

	bool collidable = false;

	TiXmlElement* pDataNode = nullptr;
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

	std::string decodedIDs;
	for (TiXmlNode* n = pDataNode->FirstChild(); n != NULL; n = n->NextSibling())
	{
		TiXmlText* text = n->ToText();
		std::string t = text->Value();
		decodedIDs = base64_decode(t);
	}

	//decompress zlib compression
	uLongf numGids = m_mapNumColumns * m_mapNumRows * sizeof(int);
	std::vector<unsigned> gids(numGids);
	uncompress((Bytef*)&gids[0], &numGids, (const Bytef*)decodedIDs.c_str(), (uLong)decodedIDs.size());

	std::vector<int> layerRow(m_mapNumColumns);

	//tile data
	std::vector<std::vector<int>> data;

	for (int j = 0; j < m_mapNumRows; j++)
	{
		data.push_back(layerRow);
	}

	for (int rows = 0; rows < m_mapNumRows; rows++)
	{
		for (int cols = 0; cols < m_mapNumColumns; cols++)
		{
			data[rows][cols] = gids[(rows * m_mapNumColumns) + cols];
		}
	}
	pTileLayer->setTileIDs(data);
	pTileLayer->setMapWidth(m_mapNumColumns);

	if (collidable)
	{
		m_pLevel->getCollisionLayers()->push_back(pTileLayer);
	}

	m_pLevel->getLayers()->push_back(pTileLayer);
}

void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement)
{
	ObjectLayer* pObjectLayer = new ObjectLayer();

	//loads objects to the object layer
	for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		int x = 0, y = 0, width = 0, height = 0, numFrames = 1, animSpeed = 1, callbackID = 0;
		std::string objType;
		std::string objTileType;

		e->Attribute("x", &x);
		e->Attribute("y", &y);
		e->Attribute("width", &width);
		e->Attribute("height", &height);
		objType = e->Attribute("name");
		objTileType = e->Attribute("type");

		//corrects the Y position from the map
		y -= height;
		
		GameObject* pGameObject = TheGameObjectFactory::Instance().create(objType);

		//get Property values
		for (TiXmlElement* property = e->FirstChildElement()->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
		{
			if (property->Attribute("name") == std::string("callbackID"))
			{
				if (property->Attribute("value") == std::string("menuToPlay"))
				{
					callbackID = 1;
				}
				else if (property->Attribute("value") == std::string("exitFromMenu"))
				{
					callbackID = 2;
				}
			}
		}

		std::vector<SDL_Rect> collisionShape;

		//goes throught the level's tilesets  
		for (unsigned int i = 0; i < m_pLevel->getTilesets()->size(); i++)
		{
			Tileset* pTileset = &m_pLevel->getTilesets()->at(i);

			if (pTileset->name == objType)
			{
				ObjectTile& rObjTile = pTileset->objTileMap.find(objTileType)->second;
				
				numFrames = rObjTile.animation.tileIDs.size();
				animSpeed = rObjTile.animation.frameDuration;
				collisionShape = rObjTile.collisionShape;
			}

		}

		//object should have own colision box or objTile containing its info
		
		pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, objTileType, numFrames, callbackID, animSpeed)));
	
		//sets the object colisionshape
		pGameObject->getColisionShape() = collisionShape;

		/*
		if (type == "Player")
		{
			m_pLevel->setPlayer(dynamic_cast<Player*>(pGameObject));
		}
		*/
		pObjectLayer->getGameObjects()->push_back(pGameObject);
	}
	m_pLevel->getLayers()->push_back(pObjectLayer);
}

void LevelParser::parseImageLayer(TiXmlElement* pImageElement)
{
	ObjectLayer* pObjectLayer = new ObjectLayer();

	int x = 0, y = 0, width = 0, height = 0, numFrames = 1, callbackID = 0, animSpeed = 1;
	std::string imageFile;
	std::string textureID;
	std::string type;

	textureID = pImageElement->Attribute("name");

	//get type from property property 
	for (TiXmlElement* e = pImageElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		//gets the type from property
		if (e->Value() == std::string("properties"))
		{
			type = e->FirstChildElement()->Attribute("value");
		}
		else
		{
			imageFile = e->Attribute("source");
			e->Attribute("width", &width);
			e->Attribute("height", &height);
		}
	}

	parseTextures(m_pLevel->getlevelAssetsLocation() + imageFile, textureID);

	GameObject* pGameObject = TheGameObjectFactory::Instance().create(type);

	pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed)));

	pObjectLayer->getGameObjects()->push_back(pGameObject);

	m_pLevel->getLayers()->push_back(pObjectLayer);
}

/* Redundunt 
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
*/

TiXmlElement* LevelParser::loadDocument(TiXmlDocument& xmlDoc,std::string assetsLocation, std::string levelFile)
{
	//load the file state
	if (!xmlDoc.LoadFile(assetsLocation + levelFile))
	{
		std::cerr << xmlDoc.ErrorDesc() << "\n";
		return nullptr;
	}

	//return the root node
	return xmlDoc.RootElement();
}

bool LevelParser::parseTextures(std::string fileName, std::string id)
{
	if (!TheTextureManager::Instance().load(fileName, id, TheSDLSystem::Instance().getRenderer()))
	{
		std::cout << "failed to load texture in LevelParser::parseTextures \n";
		return false;
	}
	return true;
}

/* to be made redundant
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
*/