#include "SystemParser.h"
#include "tinyxml.h"

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

