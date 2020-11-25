#ifndef __Parser__
#define __Parser__

#include "tinyxml.h"

#include <vector>

class Parser
{
public:
	virtual ~Parser() {}

	TiXmlElement* loadDocument(TiXmlDocument& xmlDoc, std::string& assetsLocation, std::string& file);
	
protected:
	
	void getComaSeparatedItems(const char* list, std::vector<std::string>& recipient);
};

#endif /* defined ( __Parser__ ) */

