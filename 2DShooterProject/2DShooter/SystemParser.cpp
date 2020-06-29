#include "SystemParser.h"
#include "tinyxml.h"

#include "Game.h"
#include "SDLSystem.h"
#include "InputHandler.h"
#include "SoundManager.h"

bool SystemParser::parseSystem(const char* configFile)
{
	//create XML doc
	TiXmlDocument xmlDoc;

	//load the file state
	if (!xmlDoc.LoadFile(configFile))
	{
		std::cout << "SystemParser::parseSystem could not load - " << configFile << "\n";
		std::cerr << xmlDoc.ErrorDesc() << "\n";
		return false;
	}

	//get the root element
	TiXmlElement* pRoot = xmlDoc.RootElement();

	// --------------- up to here is all the same in all parsers

	//pre declare the window root node
	TiXmlElement* pWindowRoot = nullptr;
	
	//pre declare the Input root node
	TiXmlElement* pInputRoot = nullptr;

	//pre declare the Sound root node
	TiXmlElement* pSoundRoot = nullptr;

	//pre declare the Sound root node
	TiXmlElement* pFilesRoot = nullptr;


	//get this states root node and assign it to pStateRoot
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("WINDOW"))
		{
			pWindowRoot = e;
		}
		else if (e->Value() == std::string("PERIPHERALS"))
		{
			pInputRoot = e;
		}
		else if (e->Value() == std::string("AUDIO"))
		{
			pSoundRoot = e;
		}
		else if (e->Value() == std::string("FILES"))
		{
			pFilesRoot = e;
		}
		else
		{
			std::cout << "no TiXmlElement* for " << e->Value() << " in StateParser::parseState \n";
			if (pWindowRoot && pInputRoot && pSoundRoot && pFilesRoot)
			{
				break;
			}
		}
	}

	//parse systems
	if (!parseWindow(pWindowRoot)||
		!parseInput(pInputRoot) ||
		!parseSound(pSoundRoot) ||
		!parseFiles(pFilesRoot))
	{
		return false;
	};

	return true;
}

bool SystemParser::parseWindow(TiXmlElement* pWindowRoot)
{
	if (!pWindowRoot)
	{
		return false;
	}

	const char* title = nullptr;
	int xpos, ypos, width, height, fps;
	int red, green, blue, alpha;
	bool fullScreen = false;

	for (TiXmlElement* e = pWindowRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("properties"))
		{
			title = e->Attribute("title");
			e->Attribute("window_X_Pos", &xpos);
			e->Attribute("window_Y_Pos", &ypos);
			e->Attribute("screen_Width", &width);
			e->Attribute("screen_Height", &height);
			e->Attribute("frame_Rate", &fps);
			if (e->Attribute("fullscreen") == std::string("true"))
			{
				fullScreen = true;
			}
		}
		else if (e->Value() == std::string("drawColour"))
		{
			e->Attribute("R", &red);
			e->Attribute("G", &green);
			e->Attribute("B", &blue);
			e->Attribute("Alpha", &alpha);
		}
		else
		{
			std::cout << "could not find " << e->Value() << " in " << pWindowRoot->Value() << " \n";
		}
	}

	return TheSDLSystem::Instance().init(title, xpos, ypos, width, height, fps, fullScreen, red, green, blue, alpha);

}

bool SystemParser::parseInput(TiXmlElement* pInputRoot)
{
	if (!pInputRoot)
	{
		return false;
	}

	int deadZone;

	for (TiXmlElement* e = pInputRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("joysticks"))
		{
			e->Attribute("sensibility", &deadZone);
		}
		else
		{
			std::cout << "could not find " << e->Value() << " in " << pInputRoot->Value() << " \n";
		}
	}

	TheInputHandler::Instance().init(deadZone);
	return true;
}

bool SystemParser::parseSound(TiXmlElement* pSoundRoot)
{
	if (!pSoundRoot)
	{
		return false;
	}

	int frequency, channnels, format, chunksize;

	for (TiXmlElement* e = pSoundRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("properties"))
		{
			e->Attribute("frequency", &frequency);
			e->Attribute("bits", &format);
			e->Attribute("channnels", &channnels);
			e->Attribute("chunksize", &chunksize);
		}
		else
		{
			std::cout << "could not find " << e->Value() << " in " << pSoundRoot->Value() << " \n";
		}
	}

	return TheSoundManager::Instance().init(frequency, format, channnels, chunksize);
}

bool SystemParser::parseFiles(TiXmlElement* pFilesRoot)
{
	if (!pFilesRoot)
	{
		return false;
	}

	for (TiXmlElement* e = pFilesRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("location"))
		{
			TheGame::Instance().setAssetsRoot(e->Attribute("path"));
		}
		else if (e->Value() == std::string("state"))
		{
			TheGame::Instance().setStatesFile(e->Attribute("filename"));
		}
		else if (e->Value() == std::string("level"))
		{
			int levelNumber;
			e->Attribute("stage", &levelNumber);

			TheGame::Instance().addLevelFile(levelNumber, e->Attribute("filename"));
		}
		else
		{
			std::cout << "could not find " << e->Value() << " in " << pFilesRoot->Value() << " \n";
		}
	}

	return true;
}
