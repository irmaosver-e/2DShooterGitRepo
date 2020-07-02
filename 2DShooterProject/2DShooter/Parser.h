#ifndef __Parser__
#define __Parser__

#include "tinyxml.h"

class Parser
{
public:
	TiXmlElement* loadDocument(TiXmlDocument& xmlDoc, std::string assetsLocation, std::string file);
	
private:
};

#endif /* defined ( __Parser__ ) */

