#ifndef __LevelParser__
#define __LevelParser__

#include "Parser.h"
#include "Tileset.h"
#include "Level.h"

class LevelParser : public Parser
{
public:
	LevelParser() : m_pLevel(nullptr) {}

	Level* parseLevel(std::string assetsLocation, std::string levelFile);

private:
	void parseTileset(TiXmlElement* pTilesetElement);
	void parseObjTile(TiXmlElement* pTileElement, ObjectTile& objectTile);

	void parseLayer(TiXmlElement* pLayerElement);
	
	Layer* parseTileLayer(TiXmlElement* pTileElement);
	Layer* parseObjectLayer(TiXmlElement* pObjectElement);
	Layer* parseImageLayer(TiXmlElement* pImageElement);

	bool parseTextures(std::string fileName, std::string id);

	TiXmlElement* m_mapRoot;
	std::vector<Tileset> m_tilesets;
	Level* m_pLevel;
};

#endif /* defined ( __LevelParser__ ) */