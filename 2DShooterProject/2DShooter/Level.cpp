#include "Level.h"

//#include <math.h>
//#include "TextureManager.h"
#include "Game.h"
#include "Layer.h"
//#include "TileLayer.h"

Level::~Level()
{
	for (unsigned int i = 0; i < m_layers.size(); i++)
	{
		delete m_layers[i];
	}

	m_layers.clear();
}

void Level::update()
{
	//check colisions here?
	//pass state from game singleton to collision manager?

	for (unsigned int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->update(this);
	}
}

void Level::render()
{
	for (unsigned int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->render();
	}
}
