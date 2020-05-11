#include "Level.h"

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
