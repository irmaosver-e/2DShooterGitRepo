#include "StateParser.h"

#include "SDLSystem.h"
#include "TextureManager.h"
#include "GameObjectFactory.h"

bool StateParser::parseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs)
{
	//create XML doc
	TiXmlDocument xmlDoc;

	//load the file state
	if (!xmlDoc.LoadFile(stateFile))
	{
		std::cerr << xmlDoc.ErrorDesc() << "\n";
		return false;
	}

	//get the root element
	TiXmlElement* pRoot = xmlDoc.RootElement();

	//pre declare the states root node
	TiXmlElement* pStateRoot = nullptr;

	//get this states root node and assign it to pStateRoot
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == stateID)
		{
			pStateRoot = e;
			break;
		}
	}

	//predeclare the texture root
	TiXmlElement* pTextureRoot = nullptr;

	//pre declare the object root node
	TiXmlElement* pObjectRoot = nullptr;

	//get the root node and assign it to pTextureRoot
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("TEXTURES"))
		{
			pTextureRoot = e;
		}
		else if (e->Value() == std::string("OBJECTS"))
		{
			pObjectRoot = e;
		}
		else
		{
			std::cout << "no TiXmlElement* for " << e ->Value() << " in StateParser::parseState \n" ;
			if (pTextureRoot && pObjectRoot)
			{
				break;
			}
		}
	}

	//parse textures
	parseTextures(pTextureRoot, pTextureIDs);

	//parse the objects
	parseObjects(pObjectRoot, pObjects);

	return true;
}

void StateParser::parseTextures(TiXmlElement* pTextureRoot, std::vector<std::string> *pTextureIDs)
{
	for (TiXmlElement* e = pTextureRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		std::string filenameAttribute = e->Attribute("filename");
		std::string idAttribute = e->Attribute("ID");

		pTextureIDs->push_back(idAttribute);
		if (!TheTextureManager::Instance().load(filenameAttribute, idAttribute, TheSDLSystem::Instance().getRenderer()))
		{
			std::cout << "StateParser::parseTextures -- failed to load texture " << filenameAttribute << "\n";
		}
	}
}

void StateParser::parseObjects(TiXmlElement* pObjectRoot, std::vector<GameObject*> *pObjects)
{
	for (TiXmlElement* e = pObjectRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		int x, y, width, height, numFrames, callbackID, animSpeed;
		std::string textureID;

		e->Attribute("x", &x);
		e->Attribute("y", &y);
		e->Attribute("width", &width);
		e->Attribute("height", &height);
		e->Attribute("numFrames", &numFrames);
		if (!e->Attribute("callbackID", &callbackID)) { callbackID = 0; }
		if (!e->Attribute("animSpeed", &animSpeed)) { animSpeed = 1; }

		textureID = e->Attribute("textureID");

		GameObject* pGameObject = TheGameObjectFactory::Instance().create(e->Attribute("type"));
		pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed)));
		pObjects->push_back(pGameObject);
	}
}
