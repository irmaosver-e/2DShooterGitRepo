#include "ObjectLayer.h"

void ObjectLayer::update(Level* pLevel)
{
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void ObjectLayer::render()
{
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}
