#ifndef __Level__
#define __Level__

#include <iostream>
#include <vector>
#include <map>
#include "Layer.h"
#include "LevelParser.h"
#include "Player.h"
#include "CollisionManager.h"


#include "Tileset.h"

class TileLayer;
/*
struct Animation
{
	std::string mapName;
	int frameDuration;
	std::vector<int> tileIDs;

};

struct ObjectTile
{
	int frameDuration;
	std::string type;
	
	std::vector<SDL_Rect> collisionShape;
	Animation animation;

	//collisionBox pair< Offset(X,Y), Dimentions(Width, Height)>
	std::vector<std::pair<Vector2D*, Vector2D*>*> collisionBoxes;
	std::vector<int> framesTileIDs;
};

struct Tileset
{
	int firstGridID;
	int tileWidth;
	int tileHeight;
	int spacing;	
	int margin;
	int width;
	int height;
	int numColumns;
	int tileCount;
	std::string name;
	std::map<std::string, ObjectTile*> objTileMap;
};

*/

class Level
{
public:
	~Level();

	void update();
	void render();

	std::vector<Tileset>* getTilesets() { return &m_tilesets; }
	std::vector<Layer*>* getLayers() { return &m_layers; }

	Player* getPlayer() { return m_pPlayer; }
	void setPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

	std::vector<TileLayer*>* getCollisionLayers() { return &m_collisionLayers; }
	const std::vector<TileLayer*>& getCollidableLayers() { return m_collisionLayers; }

	std::string getlevelMapFilePath() { return (m_assetsLocation + m_mapFile); }
	std::string getlevelMapFileName() { return m_mapFile; }
	std::string getlevelAssetsLocation() { return m_assetsLocation; }

private:
	friend class LevelParser;
	Level() {}
	Level(std::string location, std::string file) : m_assetsLocation(location), m_mapFile(file) {}

	Player* m_pPlayer;

	std::vector<Tileset> m_tilesets;
	std::vector<Layer*> m_layers;
	std::vector<TileLayer*> m_collisionLayers;

	std::string m_assetsLocation;
	std::string m_mapFile;
};

#endif /* defined ( __Level__ ) */

