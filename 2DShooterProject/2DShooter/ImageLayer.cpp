#include "ImageLayer.h"
#include "SDLSystem.h"

ImageLayer::~ImageLayer()
{
    for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
    {
        delete (*it);
    }
    m_gameObjects.clear();
}

//needs revision
void ImageLayer::update()
{
    // iterate through the objects
    if (!m_gameObjects.empty())
    {
        for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();)
        {
            //checks if object entered screen and update, NEEDS REVISING
            if ((*it)->getPosition().getX() <= TheSDLSystem::Instance().getScreenWidth())
            {
                (*it)->setUpdating(true);
                (*it)->update();
            }
            else
            {
                (*it)->update();
            }

            //should use collision manager to check if on screen
            //screen should have a collision box
            // check if  off screen
            if ((*it)->getPosition().getX() < (0 - (*it)->getWidth()) || (*it)->getPosition().getY() > (TheSDLSystem::Instance().getScreenHeight()))
            {
                //deleting object when it goes out of the screen
                delete* it;
                it = m_gameObjects.erase(it); // erase from vector and get new iterator
            }
            else
            {
                ++it; // increment if all ok
            }

        }
    }
}

void ImageLayer::render()
{
    for (unsigned int i = 0; i < m_gameObjects.size(); i++)
    {
        if (m_gameObjects[i]->getPosition().getX() <= TheSDLSystem::Instance().getScreenWidth())
        {
            m_gameObjects[i]->draw();
        }
    }
}
