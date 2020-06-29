#include "StateParser.h"

#include "Game.h"
#include "SDLSystem.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "GameObjectFactory.h"

bool StateParser::parseState(std::string assetsLocation, std::string stateFile, std::string stateID, 
								std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs)
{
	//create XML doc
	TiXmlDocument xmlDoc;

	//load the file state
	if (!xmlDoc.LoadFile(assetsLocation + stateFile))
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
	parseTextures(assetsLocation, pTextureRoot, pTextureIDs);

	//parse the objects
	parseObjects(pObjectRoot, pObjects);

	return true;
}

bool StateParser::parseState(GameState* pState)
{
	//create XML doc
	TiXmlDocument xmlDoc;

	std::string file = TheGame::Instance().getAssetsRoot() + TheGame::Instance().getStatesFile();
	//load the file state
	if (!xmlDoc.LoadFile(file))
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
		if (e->Value() == pState->getStateID())
		{
			pStateRoot = e;
			break;
		}
	}

	TiXmlElement* pStageElem = nullptr;
	TiXmlElement * pAudioElem = nullptr;

	//get pStageElem and pAudioElem from the root node
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("STAGE"))
		{
			pStageElem = e;
		}
		else if (e->Value() == std::string("SOUND"))
		{
			pAudioElem = e;
		}
		else
		{
			std::cout << "no TiXmlElement* for " << e->Value() << " in StateParser::parseState \n";
			if (pStageElem && pAudioElem)
			{
				break;
			}
		}
	}

	std::string path = TheGame::Instance().getAssetsRoot();
	if (pStageElem->FirstChildElement()->Attribute("subpath"))
	{
		path += pStageElem->FirstChildElement()->Attribute("subpath");
	}
	pState->setStageAssetsPath(path);
	pState->setStageMapFile(pStageElem->FirstChildElement()->Attribute("filename"));

	//create function
	parseAudio(pAudioElem);

	return true;
}

void StateParser::parseTextures(std::string assetsLocation, TiXmlElement* pTextureRoot, std::vector<std::string> *pTextureIDs)
{
	for (TiXmlElement* e = pTextureRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		std::string filename = e->Attribute("filename");
		std::string id = e->Attribute("ID");

		pTextureIDs->push_back(id);
		if (!TheTextureManager::Instance().load(assetsLocation + filename, id, TheSDLSystem::Instance().getRenderer()))
		{
			std::cout << "StateParser::parseTextures -- failed to load texture " << filename << "\n";
		}
	}
}

void StateParser::parseAudio(TiXmlElement* pAudioElem)
{
	for (TiXmlElement* e = pAudioElem->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		std::string filename = TheGame::Instance().getAssetsRoot();
		if (e->Attribute("subpath"))
		{
			filename += e->Attribute("subpath");
		}
		filename += e->Attribute("filename");

		if (e->Value() == std::string("music"))
		{
			TheSoundManager::Instance().load(filename, e->Attribute("musicID"), SOUND_MUSIC);
		}
		else if (e->Value() == std::string("sfx"))
		{
			TheSoundManager::Instance().load(filename, e->Attribute("sfxID"), SOUND_SFX);
		}
		else
		{
			std::cout << "invalid value: " << e->Value() << " in STATES XML file \n";
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
