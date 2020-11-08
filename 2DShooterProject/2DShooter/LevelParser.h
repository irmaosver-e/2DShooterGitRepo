#ifndef __LevelParser__
#define __LevelParser__

#include "Parser.h"
#include "Tileset.h"
#include "Level.h"

class LevelParser : public Parser
{
public:
	LevelParser() : 
		m_pLevel(nullptr),
		m_levelMapFile(""){}

	Level* parseLevel();

	//redundant
	//Level* parseLevel(std::string assetsLocation, std::string levelFile) {}
	
	void setLevelFile(std::string& fileName) { m_levelMapFile = fileName; }

private:
	void parseTileset(TiXmlElement* pTilesetElement);
	void parseObjTile(TiXmlElement* pTileElement, ObjectTile& objectTile);

	void parseLayer(TiXmlElement* pLayerElement);
	
	Layer* parseTileLayer(TiXmlElement* pTileElement);
	Layer* parseObjectLayer(TiXmlElement* pObjectElement);
	Layer* parseImageLayer(TiXmlElement* pImageElement);
	void parseOutOfPlayLayers(TiXmlElement* pOutElement);

	bool parseTextures(std::string& fileName, std::string id);

	void resetParser();

	TiXmlElement* m_mapRoot;
	std::vector<Tileset> m_tilesets;
	Level* m_pLevel;

	std::map<std::string, std::vector<ObjectTile>> m_objectTileOwners;

	std::string m_levelMapFile;
};

#endif /* defined ( __LevelParser__ ) */