#ifndef __LevelParser__
#define __LevelParser__

#include "tinyxml.h"
#include "base64.h"

#include "Level.h"
#include "Game.h"
#include "TextureManager.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
#include "GameObjectFactory.h"
#include "Player.h"


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