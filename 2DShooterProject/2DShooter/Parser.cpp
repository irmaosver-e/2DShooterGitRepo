#include "Parser.h"

TiXmlElement* Parser::loadDocument(TiXmlDocument& xmlDoc, std::string assetsLocation, std::string file)
{
	//load the file state
	if (!xmlDoc.LoadFile(assetsLocation + file))
	{
		std::cerr << xmlDoc.ErrorDesc() << "\n";
		return nullptr;
	}

	//return the root node
	return xmlDoc.RootElement();
}

