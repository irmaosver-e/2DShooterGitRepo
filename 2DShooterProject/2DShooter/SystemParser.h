#ifndef __SystemParser__
#define __SystemParser__

#include "tinyxml.h"

class SystemParser
{
public:
	SystemParser() {}
	~SystemParser() {}
	bool parseSystem(const char* configFile);

private:
	bool parseWindow(TiXmlElement* pWindowRoot);
	bool parseInput(TiXmlElement* pInputRoot);
	bool parseSound(TiXmlElement* pSoundRoot);
	bool parseFiles(TiXmlElement* pFilesRoot);
};

#endif /* defined ( __SystemParser__ ) */
