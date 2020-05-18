#ifndef __LevelParser__
#define __LevelParser__

#include <iostream>
#include <vector>
#include "tinyxml.h"

class Level;
struct Tileset;
class Layer;
class TileLayer;

class LevelParser
{
public:
	Level* parseLevel(const char* levelFile);

private:
	void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
	void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers,
						const std::vector<Tileset>* pTilesets, std::vector<TileLayer*> *pCollisionLayers);

	bool parseTextures(std::string fileName, std::string id);
	void parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*>* pLayers, Level* pLevel);

	int m_tileSize;
	int m_width;
	int m_height;

	std::string m_assetsLocation;
};

#endif /* defined ( __LevelParser__ ) */