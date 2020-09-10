#ifndef __TileLayer__
#define __TileLayer__

#include <vector>

#include "Vector2D.h"
#include "Layer.h"
#include "Level.h"

class TileLayer : public Layer
{
public:
	TileLayer(const std::vector<Tileset>& tilesets);
	virtual ~TileLayer() {}

	virtual void update(Level* pLevel);
	virtual void render();

	void setTileIDs(const std::vector<std::vector<int>>& data) { m_tileIDs = data; }

	int& getTileWidth() { return m_tileWidth; }
	int& getTileHeight() { return m_tileHeight; }
	int& getNumColumns() { return m_numColumns; }
	int& getNumRows() { return m_numRows; }

	void setMapWidth(int mapWidth) { m_mapWidth = mapWidth; }

	const std::vector<std::vector<int>>& getTileIDs() { return m_tileIDs; }

	Tileset getTilesetByID(int tileID);

	const Vector2D getPosition() { return m_position; }

private:
	int m_numColumns;
	int m_numRows;
	int m_tileSize;

	int m_tileWidth;
	int m_tileHeight;

	int m_mapWidth;
	
	Vector2D m_position;
	Vector2D m_velocity;

	const std::vector<Tileset> m_tilesets;
	std::vector<std::vector<int>> m_tileIDs;
};

#endif /* defined ( __TileLayer__ ) */