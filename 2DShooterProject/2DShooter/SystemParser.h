#ifndef __SystemParser__
#define __SystemParser__

#include "tinyxml.h"

class SystemParser
{
public:
	SystemParser() {}
	~SystemParser() {}

	bool parseSystem(const char* configFile, const char* title, int &xpos, int &ypos, int &width, int &height, int& fps, bool &fullScreen,
					int &drawColour_R, int &drawColour_G, int &drawColour_B, int &drawColour_A);
	
	bool parseSystem(const char* configFile);

private:
	bool parseWindow(TiXmlElement* pWindowRoot);
};

#endif /* defined ( __SystemParser__ ) */
