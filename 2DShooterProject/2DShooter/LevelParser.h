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
	Level* parseLevel(std::string assetsLocation, std::string levelFile);

private:
	void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets, std::string assetsLocation);
	void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers,
						const std::vector<Tileset>* pTilesets, std::vector<TileLayer*> *pCollisionLayers);

	bool parseTextures(std::string fileName, std::string id);
	void parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*>* pLayers, Level* pLevel);

	int m_tileSize;
	int m_width;
	int m_height;
};

#endif /* defined ( __LevelParser__ ) */