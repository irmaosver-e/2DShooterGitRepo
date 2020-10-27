#include "LevelParser.h"

#include <string>
#include "TextureManager.h"
#include "SoundManager.h"
#include "CollisionManager.h"
#include "BulletHandler.h"
#include "ObjectSpawner.h"
#include "ObjectLayer.h"
#include "ImageLayer.h"
#include "TileLayer.h"
#include "GameObjectFactory.h"
#include "base64.h"
#include "zlib.h"
#include "Cursor.h"

#include "HUD.h"

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
					getComaSeparatedItems(vsCollision->Attribute("value"), objColType.collidesAgainst);
				}
				else if (vsCollision->Attribute("name") == std::string("VsLayerCollision"))	
				{
					getComaSeparatedItems(vsCollision->Attribute("value"), objColType.collidesAgainstLayer);
				}
			}
		}
		else if (e->Value() == std::string("objectgroup"))
		{
			
			for (TiXmlElement* object = e->FirstChildElement(); object != NULL; object = object->NextSiblingElement())
			{
				//parse the colision shape boxes
				if (object->Attribute("name") == std::string("collisionBox"))
				{
					SDL_Rect collisionBox;

					object->Attribute("x", &collisionBox.x);
					object->Attribute("y", &collisionBox.y);
					object->Attribute("width", &collisionBox.w);
					object->Attribute("height", &collisionBox.h);

					objectTile.collisionShape.push_back(collisionBox);
				}
				
				//parse the firingPoints to bulletHandler
				if (object->Attribute("name") == std::string("firingPoint"))
				{
					FiringPoint firingPoint;
					object->QueryFloatAttribute("x", firingPoint.position.getXPtr());
					object->QueryFloatAttribute("y", firingPoint.position.getYPtr());
					firingPoint.bulletType = object->Attribute("type");

					TheBulletHandler::Instance().registerFiringPoint(objectTile.type, firingPoint);
				}
				if (object->Attribute("name") == std::string("anchor"))
				{
					//to implement goes here first
					LoaderParams bulletTypeParams;

					//Vector2Df bulletAnchorVec2D;
					object->QueryFloatAttribute("x", bulletTypeParams.getAnchorPointPtr()->getXPtr());
					object->QueryFloatAttribute("y", bulletTypeParams.getAnchorPointPtr()->getYPtr());


					TheBulletHandler::Instance().registerBulletType(object->Attribute("type"), bulletTypeParams);
				}

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

	pTileLayer->getLayerNameRef() = pTileElement->Attribute("name");

	TiXmlElement* pDataNode = nullptr;
	for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("properties"))
		{
			for (TiXmlElement* layerProperty = e->FirstChildElement(); layerProperty != NULL; layerProperty = layerProperty->NextSiblingElement())
			{
				if (layerProperty->Attribute("name") == std::string("ScrollSpeed"))
				{
					layerProperty->QueryFloatAttribute("value", pTileLayer->getScrollSpeedPtr());
				}
			}

		}
		else if (e->Value() == std::string("data"))
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

	//sets the name of the object layer
	pObjectLayer->getLayerNameRef() = pObjectElement->Attribute("name");

	//loads elements from the object layer
	for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{		
		//gets the layer properties
		if (e->Value() == std::string("properties"))
		{
			for (TiXmlElement* layerProperty = e->FirstChildElement(); layerProperty != NULL; layerProperty = layerProperty->NextSiblingElement())
			{
				if (layerProperty->Attribute("name") == std::string("ScrollSpeed"))
				{
					layerProperty->QueryFloatAttribute("value", pObjectLayer->getScrollSpeedPtr());
				}
			}
		}
		else
		{			
			//creates the object marker
			ObjectMarker objMarker;

			//sets the object type/subtype and position to the marker
			objMarker.objectType = e->Attribute("name");
			objMarker.objSubType = e->Attribute("type");
			e->QueryFloatAttribute("x", objMarker.objPositionMarker.getXPtr());
			
			//ajust y position of marker
			float y, height;
			e->QueryFloatAttribute("y", &y);
			e->QueryFloatAttribute("height", &height);
			objMarker.objPositionMarker.getYRef() = y - height;

			objMarker.isActive = true;

			pObjectLayer->getObjMarkersRef().push_back(objMarker);

			//register the parameters to the spawner
			std::string objSubType = e->Attribute("type");
			if (!TheObjectSpawner::Instance().checkObjParamsMap(objSubType))
			{
				LoaderParams objectParams;

				//populates the parameters
				objectParams.getTextureIDRef() = e->Attribute("type");
				e->Attribute("width", objectParams.getWidthPtr());
				e->Attribute("height", objectParams.getHeightPtr());

				//checks if the object has properties
				TiXmlElement* properties = e->FirstChildElement();
				if (properties)
				{
					for (TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
					{
						if (property->Attribute("name") == std::string("callbackID"))
						{
							if (property->Attribute("value") == std::string("menuToPlay") ||
								property->Attribute("value") == std::string("pauseToMain") ||
								property->Attribute("value") == std::string("gameOverToMain"))
							{
								objectParams.getCallbackIDRef() = 1;
							}
							else if (property->Attribute("value") == std::string("exitFromMenu") ||
								property->Attribute("value") == std::string("resumePlay") ||
								property->Attribute("value") == std::string("restartPlay"))
							{
								objectParams.getCallbackIDRef() = 2;
							}
						}
						if (property->Attribute("name") == std::string("sfx"))
						{
							objectParams.getSFXRef() = property->Attribute("value");
						}
						if (property->Attribute("name") == std::string("Lives"))
						{
							property->Attribute("value", objectParams.getLivesPtr());
						}
					}
				}

				TheObjectSpawner::Instance().registerObjParams(objSubType, objectParams);
			}
			
			//spawns the objects on screen
			TheObjectSpawner::Instance().spawnObject(*pObjectLayer, pObjectLayer->getObjMarkersRef().back());

			
			//looks for the player and sets it to the map
			if (e->Attribute("name") == std::string("Player"))
			{
				m_pLevel->setPlayer(dynamic_cast<Player*>(pObjectLayer->getGameObjects()->back()));
			}
			
		}
	}

	m_pLevel->getObjectLayers()->push_back(pObjectLayer);

	return pObjectLayer;
}

Layer* LevelParser::parseImageLayer(TiXmlElement* pImageElement)
{
	ImageLayer* pImageLayer = new ImageLayer();
	LoaderParams imageParams;
	
	std::string imageFile, type;

	pImageLayer->getLayerNameRef() = pImageElement->Attribute("name");

	imageParams.getTextureIDRef() = pImageElement->Attribute("name");

	//get type from imagelayer property 
	for (TiXmlElement* e = pImageElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		//gets the type from property
		if (e->Value() == std::string("properties"))
		{
			for (TiXmlElement* layerProperty = e->FirstChildElement(); layerProperty != NULL; layerProperty = layerProperty->NextSiblingElement())
			{
				if (layerProperty->Attribute("name") == std::string("ScrollSpeed"))
				{
					layerProperty->QueryFloatAttribute("value", pImageLayer->getScrollSpeedPtr());
				}
				else if (layerProperty->Attribute("name") == std::string("type"))
				{
					type = layerProperty->Attribute("value");
				}
			}
		}
		else
		{
			imageFile = e->Attribute("source");
			e->Attribute("width", imageParams.getWidthPtr());
			e->Attribute("height", imageParams.getHeightPtr());
		}
	}

	parseTextures(m_pLevel->getlevelAssetsLocation() + imageFile, imageParams.getTextureID());

	GameObject* pGameObject = TheGameObjectFactory::Instance().create(type);

	pGameObject->load(imageParams);

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
			ObjectLayer* pObjectLayer = nullptr;

			//if its a HUD DO NOT add to object layer, HUDs belong to objects
			if (pOutElement->Attribute("name") == std::string("OUT_OF_PLAY_AREA") &&
				e->Attribute("name") != std::string("ViewPort"))
			{
				pObjectLayer = new ObjectLayer();
				pObjectLayer->getLayerNameRef() = e->Attribute("name");

				m_pLevel->getObjectLayers()->push_back(pObjectLayer);
			}


			//if the object layer is the Bullets Layer, poppulate the bulletHandler 
			if (e->Attribute("name") == std::string("Bullets"))
			{
				TheBulletHandler::Instance().registerBulletLayer(pObjectLayer);
				//TheBulletHandler::Instance().registerBulletLayerName(e->Attribute("name"));

				//goes through every object in the layer
				for (TiXmlElement* pObjElement = e->FirstChildElement(); pObjElement != NULL; pObjElement = pObjElement->NextSiblingElement())
				{
					LoaderParams* pBulletParam = TheBulletHandler::Instance().getBulletTypeParam(pObjElement->Attribute("name"));

					pObjElement->QueryFloatAttribute("x", pBulletParam->getInitialPosPtr()->getXPtr());
					pObjElement->QueryFloatAttribute("y", pBulletParam->getInitialPosPtr()->getYPtr());
					pObjElement->Attribute("width", pBulletParam->getWidthPtr());
					pObjElement->Attribute("height", pBulletParam->getHeightPtr());
					
					pBulletParam->getTextureIDRef() = pObjElement->Attribute("type");		

					TheBulletHandler::Instance().getBulletTypeParam(pObjElement->Attribute("name"));
				}
			}
			if (pOutElement->Attribute("name") == std::string("HUDs"))
			{

				HUD* pHUD = dynamic_cast<HUD*>(TheGameObjectFactory::Instance().create("HUD"));
				
				//can use pHUDParam to set its position, 0,0 by default in viewport
				LoaderParams pHUDParam;
				pHUD->load(pHUDParam);

				//goes through every object in the layer adding it to the HUD
				for (TiXmlElement* pObjElement = e->FirstChildElement(); pObjElement != NULL; pObjElement = pObjElement->NextSiblingElement())
				{
					//adds the text boxes to the HUD
					if (pObjElement->Attribute("name") == std::string("TextBox"))
					{
						GameObject* pTextBox = TheGameObjectFactory::Instance().create("TextBox");
						LoaderParams pTextBoxParam;

						pObjElement->QueryFloatAttribute("x", pTextBoxParam.getInitialPosPtr()->getXPtr());
						pObjElement->QueryFloatAttribute("y", pTextBoxParam.getInitialPosPtr()->getYPtr());

						//the pObjElement->FirstChildElement() is the text element 
						pTextBoxParam.getFontTypeRef() = pObjElement->FirstChildElement()->Attribute("fontfamily");
						pTextBoxParam.getTextBoxMessageRef() = pObjElement->FirstChildElement()->GetText();
						
						pTextBox->load(pTextBoxParam);

						pHUD->addTextBox(pTextBox);

					}
					if (pObjElement->Attribute("name") == std::string("AnimatedGraphic"))
					{
						//adds the animated Graphics to the HUD
						std::cout << "AnimatedGraphic \n";
					}
				}

				//the HUD belongs to the Player
				if (e->Attribute("name") == std::string("Player"))
				{
					m_pLevel->getPlayer()->setHUDPtr(pHUD);
				}

				//pObjectLayer->getGameObjectsRef().push_back(pHUD);

				//pGameObject->load(pHUDParam);

				//pImageLayer->getGameObjects()->push_back(pGameObject);

				//m_pLevel->getImageLayers()->push_back(pImageLayer);
			}
	
			pOutLayer = pObjectLayer;
			
		}
		else if (e->Value() == std::string("group"))
		{
			parseOutOfPlayLayers(e);
		}


		if (pOutLayer)
		{
			m_pLevel->getLayers()->push_back(pOutLayer);
		}
	}
}

bool LevelParser::parseTextures(std::string fileName, std::string id)
{
	if (!TheTextureManager::Instance().loadTextureFromFile(fileName, id))
	{
		std::cout << "failed to load texture in LevelParser::parseTextures \n";
		return false;
	}
	return true;
}
