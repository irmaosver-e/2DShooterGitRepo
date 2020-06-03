#include "SystemParser.h"
#include "tinyxml.h"

#include "SDLSystem.h"

bool SystemParser::parseSystem(const char* filePath, const char* title, int& xpos, int& ypos, int& width, int& height, int& fps, bool& fullScreen,
								int& drawColour_R, int& drawColour_G, int& drawColour_B, int& drawColour_A)
{
	//create XML doc
	TiXmlDocument xmlDoc;

	//load the file state
	if (!xmlDoc.LoadFile(filePath))
	{
		std::cout << "SystemParser::parseSystem could not load - " << filePath << "\n";
		std::cerr << xmlDoc.ErrorDesc() << "\n";
	}

	//get the root element
	TiXmlElement* pRoot = xmlDoc.RootElement();

	//pre declare the window root node
	TiXmlElement* pWindowRoot = nullptr;

	//get this states root node and assign it to pStateRoot
	if (pRoot->FirstChildElement()->Value() == std::string("WINDOW"))
	{
		pWindowRoot = pRoot->FirstChildElement();
	}
	else
	{
		std::cout << "<WINDOW> must be the first element in " << filePath << " \n";
	}

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
			if (e->Attribute("fullscreen") == std::string("false"))
			{
				fullScreen = false;
			}
			else
			{
				fullScreen = true;
			}
		}
		else if (e->Value() == std::string("drawColour"))
		{
			e->Attribute("R", &drawColour_R);
			e->Attribute("G", &drawColour_G);
			e->Attribute("B", &drawColour_B);
			e->Attribute("Alpha", &drawColour_A);
		}
		else
		{
			std::cout << "could not find " << e->Value() << " in " << filePath << " \n";
		}
	}

	return true;
}

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

	//get this states root node and assign it to pStateRoot
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("WINDOW"))
		{
			pWindowRoot = e;
			break;
		}
		else
		{
			std::cout << "no TiXmlElement* for " << e->Value() << " in StateParser::parseState \n";
		}
	}

	//parse window
	if (!parseWindow(pWindowRoot))
	{
		return false;
	}

	//parse the objects
	//parseInputHandler(pObjectRoot, pObjects);

	return true;
}

bool SystemParser::parseWindow(TiXmlElement* pWindowRoot)
{
	const char* title = nullptr;
	int xpos, ypos, width, height, fps;
	int red, green, blue, alpha;
	bool fullScreen;

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
			if (e->Attribute("fullscreen") == std::string("false"))
			{
				fullScreen = false;
			}
			else
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

