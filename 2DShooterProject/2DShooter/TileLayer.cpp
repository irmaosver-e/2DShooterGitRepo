#include "TileLayer.h"

#include "SDLSystem.h"
#include "Game.h"
#include "TextureManager.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset>& tilesets) : m_tileSize(tileSize), m_tilesets(tilesets), m_position(0,0), m_velocity(0,0)
{
	m_numColumns = (TheSDLSystem::Instance().getScreenWidth() / m_tileSize) + 1;
	m_numRows = TheSDLSystem::Instance().getScreenHeight() / m_tileSize;
}

TileLayer::TileLayer(const std::vector<Tileset>& tilesets) : 
	m_tileWidth(1), m_tileHeight(1), m_numColumns(1), m_numRows(1),
	m_tilesets(tilesets), m_position(0, 0), m_velocity(0, 0)
{
}

void TileLayer::update(Level* pLevel)
{
	if (m_position.getX() < ((m_mapWidth * m_tileSize) - TheSDLSystem::Instance().getScreenWidth()) - m_tileSize)
	{
		m_velocity.setX(TheGame::Instance().getScrollSpeed());
		m_position += m_velocity;

	}
	else
	{
		m_velocity.setX(0);
	}
}

void TileLayer::render()
{
	int x, y, x2, y2 = 0;

	x = int(m_position.getX()) / m_tileWidth;
	y = int(m_position.getY()) / m_tileHeight;

	x2 = int(m_position.getX()) % m_tileWidth;
	y2 = int(m_position.getY()) % m_tileHeight;

	for (int i = 0; i < m_numRows; i++)
	{
		for (int j = 0; j < m_numColumns; j++)
		{		
			int id = m_tileIDs[i + y][j + x];

			if (id == 0)
			{
				continue;
			}

			Tileset tileset = getTilesetByID(id);
			id--;

			int tile_Y_offset = 0;
			if (tileset.tileHeight != m_tileHeight)
			{
				tile_Y_offset = tileset.tileHeight - m_tileHeight;
			}

			int tile_X_pos = (j * m_tileWidth) - x2;
			int tile_Y_pos = ((i * m_tileHeight) - y2) - tile_Y_offset;
			int tileRow = (id - (tileset.firstGridID - 1)) / tileset.numColumns;
			int tileColumn = (id - (tileset.firstGridID - 1)) % tileset.numColumns;
			
			TheTextureManager::Instance().drawTile(tileset.name, tileset.margin, tileset.spacing,
													tile_X_pos, tile_Y_pos, tileset.tileWidth, tileset.tileHeight, 
													tileRow, tileColumn, TheSDLSystem::Instance().getRenderer());
		}
	}
}

Tileset TileLayer::getTilesetByID(int tileID)
{
	for (unsigned int i = 0; i < m_tilesets.size(); i++)
	{
		if (i + 1 <= m_tilesets.size() - 1)
		{
			if (tileID >= m_tilesets[i].firstGridID &&
				tileID < m_tilesets[i + 1].firstGridID)
			{
				return m_tilesets[i];
			}
		}
		else
		{
			return m_tilesets[i];
		}
	}
	std::cout << " returning empty tileset \n";
	Tileset t;
	return t;
}
