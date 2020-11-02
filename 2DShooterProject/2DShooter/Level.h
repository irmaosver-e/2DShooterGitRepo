#ifndef __Level__
#define __Level__

#include "Player.h"
#include "Layer.h"
#include "ObjectLayer.h"
#include "TileLayer.h"
#include "ImageLayer.h"

class Level
{
public:
	~Level();

	void update();
	void render();

	std::vector<Layer*>* getLayers() { return &m_layers; }

	Player* getPlayer() { return m_pPlayer; }
	void setPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

	std::vector<TileLayer*>* getTileLayers() { return &m_tileLayers; }
	TileLayer* getTileLayerByName(std::string tileLayer);

	std::vector<ObjectLayer*>* getObjectLayers() { return &m_objectLayers; }
	ObjectLayer* getObjectLayerByName(std::string objLayer);
	void getObjectsfromLayers(std::vector<GameObject*>& objContainer, std::string objType = "all", std::string layer = "all");

	std::vector<ImageLayer*>* getImageLayers() { return &m_imageLayers; }
	//ImageLayer* getImageLayerByName(std::string imageLayer);

	std::string getlevelMapFilePath() { return (m_assetsLocation + m_mapFile); }
	std::string getlevelMapFileName() { return m_mapFile; }
	std::string getlevelAssetsLocation() { return m_assetsLocation; }

private:
	friend class LevelParser;

	Level() {}

	//possibly redundant
	Level(std::string location, std::string file) : m_assetsLocation(location), m_mapFile(file) {}

	Player* m_pPlayer;

	std::vector<Layer*> m_layers;
	std::vector<ObjectLayer*> m_objectLayers;
	std::vector<TileLayer*> m_tileLayers;
	std::vector<ImageLayer*> m_imageLayers;

	//possibly redundant
	std::string m_assetsLocation;
	std::string m_mapFile;

};

#endif /* defined ( __Level__ ) */

