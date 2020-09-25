#include "LevelParser.h"

#include <string>
#include "SDLSystem.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "CollisionManager.h"
#include "ObjectLayer.h"
#include "ImageLayer.h"
#include "TileLayer.h"
#include "GameObjectFactory.h"
#include "base64.h"
#include "zlib.h"
#include "Cursor.h"

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

Level* LevelParser::parseLevel(std::string assetsLocation, std::string levelFile)
{
	m_pLevel = new Level(assetsLocation, levelFile);

	TiXmlDocument xmlDoc;

	m_mapRoot = loadDocument(xmlDoc, assetsLocation, levelFile);

	TiXmlElement* pProperties = NULL;
	std::vector<TiXmlElement*> pLayerElements;

	//parse textures added to property
	for (TiXmlElement* e = m_mapRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
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

	TiXmlDocument tilesetDoc;

	TiXmlElement* pTilesetRoot = loadDocument(tilesetDoc, m_pLevel->getlevelAssetsLocation(), pTilesetElement->Attribute("source"));

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
			//objTile.animation.sourceRows = tileset.tileCount / tileset.numColumns;

			tileset.objTileMap[objTile.type] = objTile;

			//register the animation with the textureManager
			TheTextureManager::Instance().getAnimationMap()[objTile.type] = objTile.animation;
		}
	}

	//to be revised !!!!!!  maybe better have tilesets here  !!!!!!!!!!!!!!!!!!!!
	m_tilesets.push_back(tileset);
}

void LevelParser::parseObjTile(TiXmlElement* pTileElement, ObjectTile& objectTile)
{
	//should load the collision type somewhere here probably

	objectTile.type = pTileElement->Attribute("type");
	
	ObjectCollisionType objColType;
	objColType.name = objectTile.type;
	
	for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("properties"))
		{
			for (TiXmlElement* vsCollision = e->FirstChildElement(); vsCollision != NULL; vsCollision = vsCollision->NextSiblingElement())
			{
				if (vsCollision->Attribute("name") == std::string("VsCollision"))
				{
					objColType.collidesAgainst.push_back(vsCollision->Attribute("value"));
				}
				else if (vsCollision->Attribute("name") == std::string("VsLayerCollision"))
				{
					objColType.collidesAgainstLayer.push_back(vsCollision->Attribute("value"));
				}
			}
		}
		else if (e->Value() == std::string("objectgroup"))
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
			objColType.collisionShape = objectTile.collisionShape;
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

	TheCollisionManager::Instance().addCollisionObject(objColType);
}

void LevelParser::parseLayer(TiXmlElement* pLayerElement)
{	
	Layer* pLayer = nullptr;

	if (pLayerElement->Value() == std::string("group"))
	{
		for (TiXmlElement* e = pLayerElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
		{
			parseLayer(e);
		}
	}
	else if (pLayerElement->Value() == std::string("layer"))
	{
		pLayer = parseTileLayer(pLayerElement);
	}
	else if (pLayerElement->Value() == std::string("imagelayer"))
	{
		pLayer = parseImageLayer(pLayerElement);
	}
	else if (pLayerElement->Value() == std::string("objectgroup"))
	{
		pLayer = parseObjectLayer(pLayerElement);
	}
	else
	{
		std::cout << "invalid layer Type: " << pLayerElement->Value() << " in level map \n";
	}

	if (pLayer)
	{
		m_pLevel->getLayers()->push_back(pLayer);
	}
}

Layer* LevelParser::parseTileLayer(TiXmlElement* pTileElement)
{
	TileLayer* pTileLayer = new TileLayer(m_tilesets);
	
	m_mapRoot->Attribute("tilewidth", &pTileLayer->getTileWidth());
	m_mapRoot->Attribute("tileheight", &pTileLayer->getTileHeight());
	m_mapRoot->Attribute("width", &pTileLayer->getNumColumns());
	m_mapRoot->Attribute("height", &pTileLayer->getNumRows());

	pTileLayer->getLayerName() = pTileElement->Attribute("name");

	TiXmlElement* pDataNode = nullptr;
	for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
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

	int mapNumColumns = pTileLayer->getNumColumns();
	int mapNumRows = pTileLayer->getNumRows();
	//decompress zlib compression
	uLongf numGids = mapNumColumns * mapNumRows * sizeof(int);
	std::vector<unsigned> gids(numGids);
	uncompress((Bytef*)&gids[0], &numGids, (const Bytef*)decodedIDs.c_str(), (uLong)decodedIDs.size());

	std::vector<int> layerRow(mapNumColumns);

	//tile data
	std::vector<std::vector<int>> data;

	for (int j = 0; j < mapNumRows; j++)
	{
		data.push_back(layerRow);
	}

	for (int rows = 0; rows < mapNumRows; rows++)
	{
		for (int cols = 0; cols < mapNumColumns; cols++)
		{
			data[rows][cols] = gids[(rows * mapNumColumns) + cols];
		}
	}
	pTileLayer->setTileIDs(data);
	pTileLayer->setMapWidth(mapNumColumns);

	m_pLevel->getTileLayers()->push_back(pTileLayer);

	return pTileLayer;
}

Layer* LevelParser::parseObjectLayer(TiXmlElement* pObjectElement)
{
	ObjectLayer* pObjectLayer = new ObjectLayer();

	//loads objects to the object layer
	for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		int x = 0, y = 0, width = 0, height = 0, numFrames = 1, animSpeed = 1, callbackID = 0;
		std::string sfx;
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

		//checks if the object has properties
		TiXmlElement* properties = e->FirstChildElement();
		if(properties)
		{
			for (TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
			{
				if (property->Attribute("name") == std::string("callbackID"))
				{
					if (property->Attribute("value") == std::string("menuToPlay") ||
						property->Attribute("value") == std::string("pauseToMain") ||
						property->Attribute("value") == std::string("gameOverToMain"))
					{
						callbackID = 1;
					}
					else if (property->Attribute("value") == std::string("exitFromMenu") ||
							 property->Attribute("value") == std::string("resumePlay") ||
							 property->Attribute("value") == std::string("restartPlay"))
					{
						callbackID = 2;
					}
				}
				if (property->Attribute("name") == std::string("sfx"))
				{
					sfx = property->Attribute("value");
				}
			}
		}

		std::vector<SDL_Rect> collisionShape;

		//goes throught the level's tilesets  
		for (unsigned int i = 0; i < m_tilesets.size(); i++)
		{
			if (m_tilesets[i].name == objType)
			{
				ObjectTile& rObjTile = m_tilesets[i].objTileMap.find(objTileType)->second;
				
				numFrames = rObjTile.animation.tileIDs.size();
				animSpeed = rObjTile.animation.frameDuration;
				collisionShape = rObjTile.collisionShape;
			}

		}
		
		pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, objTileType, numFrames, callbackID, animSpeed, sfx)));

		if (objType == "Player")
		{
			m_pLevel->setPlayer(dynamic_cast<Player*>(pGameObject));
		}
		
		pObjectLayer->getGameObjects()->push_back(pGameObject);
	}

	m_pLevel->getObjectLayers()->push_back(pObjectLayer);

	return pObjectLayer;
}

Layer* LevelParser::parseImageLayer(TiXmlElement* pImageElement)
{
	ImageLayer* pImageLayer = new ImageLayer();

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

	pImageLayer->getGameObjects()->push_back(pGameObject);

	return pImageLayer;
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
