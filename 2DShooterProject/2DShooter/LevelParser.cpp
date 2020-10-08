#include "LevelParser.h"

#include <string>
#include "SDLSystem.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "CollisionManager.h"
#include "BulletHandler.h"
#include "ObjectLayer.h"
#include "ImageLayer.h"
#include "TileLayer.h"
#include "GameObjectFactory.h"
#include "base64.h"
#include "zlib.h"
#include "Cursor.h"

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
		if(pLayerElement->Attribute("name") == std::string("OUT_OF_PLAY_AREA"))
		{ 
			parseOutOfPlayLayers(pLayerElement);
		
		}
		else
		{
			for (TiXmlElement* e = pLayerElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
			{
				parseLayer(e);
			}
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

	pTileLayer->refLayerName() = pTileElement->Attribute("name");

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
	pObjectLayer->refLayerName() = pObjectElement->Attribute("name");

	//loads objects to the object layer
	for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		int x = 0, y = 0, width = 0, height = 0, numFrames = 1, animSpeed = 1, callbackID = 0, lives = 1;
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
				if (property->Attribute("name") == std::string("Lives"))
				{
					property->Attribute("value", &lives);
				}
			}
		}

		pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, objTileType, numFrames, lives, callbackID, animSpeed, sfx)));

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
	pImageLayer->refLayerName() = pImageElement->Attribute("name");

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

	m_pLevel->getImageLayers()->push_back(pImageLayer);

	return pImageLayer;
}

void LevelParser::parseOutOfPlayLayers(TiXmlElement* pOutElement)
{
	Layer* pOutLayer = nullptr;

	for (TiXmlElement* e = pOutElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("objectgroup"))
		{
			ObjectLayer* pObjectLayer = new ObjectLayer();
			pObjectLayer->refLayerName() = e->Attribute("name");

			m_pLevel->getObjectLayers()->push_back(pObjectLayer);
			pOutLayer = pObjectLayer;

			//if the object layer is the Bullets Layer, poppulate the bulletHandler 
			if (e->Attribute("name") == std::string("Bullets"))
			{
				TheBulletHandler::Instance().registerBulletLayer(pObjectLayer);
				//TheBulletHandler::Instance().registerBulletLayerName(e->Attribute("name"));

				//goes through every object in the layer
				for (TiXmlElement* pObjElement = e->FirstChildElement(); pObjElement != NULL; pObjElement = pObjElement->NextSiblingElement())
				{
					int x = 0, y = 0, width = 0, height = 0, numFrames = 1, animSpeed = 1, callbackID = 0, lives = 1;
					std::string sfx;
					std::string objType;
					std::string objTileType;

					pObjElement->Attribute("x", &x);
					pObjElement->Attribute("y", &y);
					pObjElement->Attribute("width", &width);
					pObjElement->Attribute("height", &height);
					objType = pObjElement->Attribute("name");
					objTileType = pObjElement->Attribute("type");

					TheBulletHandler::Instance().registerBulletType(objType, 
						new LoaderParams(x, y, width, height, objTileType, numFrames, lives, callbackID, animSpeed, sfx));
				}
			}
		}


		if (pOutLayer)
		{
			m_pLevel->getLayers()->push_back(pOutLayer);
		}
	}
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
