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

void Parser::getComaSeparatedItems(const char* list, std::vector<std::string>& recipient)
{
	std::stringstream comaSeparatedList(list);

	while (comaSeparatedList.good())
	{
		std::string resultItem;
		getline(comaSeparatedList, resultItem, ',');

		//clear result Item from spaces
		resultItem.erase(remove(resultItem.begin(), resultItem.end(), ' '), resultItem.end());

		recipient.push_back(resultItem);
	}
}

