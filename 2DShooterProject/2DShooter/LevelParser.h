#ifndef __LevelParser__
#define __LevelParser__

#include <iostream>
#include <vector>
#include "tinyxml.h"
#include "Tileset.h"
#include "Level.h"

class LevelParser
{
public:
	LevelParser() : m_pLevel(nullptr) {}

	Level* parseLevel(std::string assetsLocation, std::string levelFile);

private:
	void parseTileset(TiXmlElement* pTilesetElement);
	void parseObjTile(TiXmlElement* pTileElement, ObjectTile& objectTile);

	void parseLayer(TiXmlElement* pLayerElement);
	
	void parseTileLayer(TiXmlElement* pTileElement);
	void parseObjectLayer(TiXmlElement* pObjectElement);
	void parseImageLayer(TiXmlElement* pImageElement);

	bool parseTextures(std::string fileName, std::string id);
	TiXmlElement* loadDocument(TiXmlDocument& xmlDoc, std::string assetsLocation, std::string levelFile);

	TiXmlElement* m_mapRoot;
	std::vector<Tileset> m_tilesets;
	Level* m_pLevel;
};

#endif /* defined ( __LevelParser__ ) */