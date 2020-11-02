#include "SystemParser.h"
#include "tinyxml.h"

#include "ParserManager.h"
#include "SDLSystem.h"
#include "InputHandler.h"
#include "SoundManager.h"
#include "TextManager.h"

bool SystemParser::parseSystem(const char* configFile)
{
	//create XML doc
	TiXmlDocument xmlDoc;

	std::string configStr = configFile;
	TiXmlElement* pRoot = loadDocument(xmlDoc, TheParserManager::Instance().m_rootPath, configStr);

	//pre declare the window root node
	TiXmlElement* pWindowRoot = nullptr;
	
	//pre declare the Input root node
	TiXmlElement* pInputRoot = nullptr;

	//pre declare the Sound root node
	TiXmlElement* pSoundRoot = nullptr;

	//pre declare the Fonts root node
	TiXmlElement* pFontsRoot = nullptr;

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
		else if (e->Value() == std::string("FONTS"))
		{
			pFontsRoot = e;
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
	if (!parseFiles(pFilesRoot) ||
		!parseWindow(pWindowRoot) ||
		!parseInput(pInputRoot) ||
		!parseSound(pSoundRoot) ||
		!parseFonts(pFontsRoot))
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

	std::string iconPath = TheParserManager::Instance().m_rootPath + TheParserManager::Instance().m_imagesFolder;
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
		else if (e->Value() == std::string("iconParamn"))
		{
			iconPath += e->Attribute("fileName");
			title = e->Attribute("title");
		}
		else
		{
			std::cout << "could not find " << e->Value() << " in " << pWindowRoot->Value() << " \n";
		}
	}


	return TheSDLSystem::Instance().init(title, iconPath.c_str(), xpos, ypos, width, height, fps, fullScreen, red, green, blue, alpha);

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

bool SystemParser::parseFonts(TiXmlElement* pFontsRoot)
{
	if (!pFontsRoot)
	{
		return false;
	}

	TheTextManager::Instance().init();
	TheTextManager::Instance().setFontRepositoryPath(TheParserManager::Instance().m_rootPath + TheParserManager::Instance().m_fontsFolder);
	for (TiXmlElement* e = pFontsRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("type"))
		{
			int fontSize;
			e->Attribute("size", &fontSize);

			TheTextManager::Instance().loadFont(e->Attribute("fontName"), fontSize, e->Attribute("filename"));
		}
		else
		{
			std::cout << "could not find " << e->Value() << " in " << pFontsRoot->Value() << " \n";
		}

	}

	return true;
}

bool SystemParser::parseFiles(TiXmlElement* pFilesRoot)
{
	if (!pFilesRoot)
	{
		return false;
	}

	for (TiXmlElement* e = pFilesRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("AssetPaths"))
		{
			TheParserManager::Instance().m_rootPath = e->Attribute("root");
			TheParserManager::Instance().m_imagesFolder = e->Attribute("images");
			TheParserManager::Instance().m_audioFolder = e->Attribute("audio");
			TheParserManager::Instance().m_fontsFolder = e->Attribute("fonts");
			TheParserManager::Instance().m_mapsFolder = e->Attribute("maps");
			TheParserManager::Instance().m_tilesetsFolder = e->Attribute("tilesets");
		}
		else if (e->Value() == std::string("statesFile"))
		{
			std::string stateFileName = e->Attribute("filename");
			TheParserManager::Instance().m_stateParser.setStateFile(stateFileName);
		}
		else if (e->Value() == std::string("level")) // SO FAR REDUNDANT!!!
		{ 
			//int levelNumber;
			//e->Attribute("stage", &levelNumber);

			//TheGame::Instance().addLevelFile(levelNumber, e->Attribute("filename"));

		}
		else
		{
			std::cout << "could not find " << e->Value() << " in " << pFilesRoot->Value() << " \n";
		}

	}

	return true;
}
