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

	// redundant ?
	std::vector<TileLayer*>* getCollisionLayers() { return &m_collisionLayers; }
	const std::vector<TileLayer*>& getCollidableLayers() { return m_collisionLayers; }
	//-----------

	std::vector<TileLayer*>* getTileLayers() { return &m_tileLayers; }
	TileLayer* getTileLayerByName(std::string tileLayer);

	std::vector<ObjectLayer*>* getObjectLayers() { return &m_objectLayers; }
	void getObjectsfromLayers(std::vector<GameObject*>& objContainer, std::string objType = "all", std::string layer = "all");

	std::string getlevelMapFilePath() { return (m_assetsLocation + m_mapFile); }
	std::string getlevelMapFileName() { return m_mapFile; }
	std::string getlevelAssetsLocation() { return m_assetsLocation; }

private:
	friend class LevelParser;
	
	//to be made redundant
	//Level() {}
	std::vector<TileLayer*> m_collisionLayers;

	//---------------

	Level(std::string location, std::string file) : m_assetsLocation(location), m_mapFile(file) {}

	Player* m_pPlayer;

	std::vector<Layer*> m_layers;
	std::vector<ObjectLayer*> m_objectLayers;
	std::vector<TileLayer*> m_tileLayers;
	//std::vector<ImageLayer*> m_imageLayers;


	std::string m_assetsLocation;
	std::string m_mapFile;

};

#endif /* defined ( __Level__ ) */

