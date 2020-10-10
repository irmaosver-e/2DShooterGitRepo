#include "ObjectLayer.h"

#include "Game.h"
#include "SDLSystem.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Level.h"


ObjectLayer::~ObjectLayer()
{
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		delete (*it);
	}
	m_gameObjects.clear();
}

void ObjectLayer::update(Level* pLevel)
{
  
    // iterate through the objects
    if (!m_gameObjects.empty())
    {
        
        for (GameObject* pGameObj : m_gameObjects)
        {
            if (pGameObj->isOn())
            {
                if (pGameObj->isInView())
                {
                    TheCollisionManager::Instance().checkCollision(pGameObj);
                    pGameObj->update();
                }
                else
                {
                    pGameObj->outOfView();
                }

            }

            /*
            if (pGameObj->isInView())
            {
                //pGameObj->turnObjOn();
                //pGameObj->setUpdating(true);
                pGameObj->update();
            }
            else
            {
                pGameObj->outOfView();
                if (pGameObj->objType() != std::string("Player"))
                {
                    pGameObj->setUpdating(false);
                    pGameObj->scroll(TheGame::Instance().getScrollSpeed());
                }
            }
            */
        }

        

        /*
        for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();)
        {
            TheCollisionManager::Instance().checkCollision(*it);

            //need revising
            if ((*it)->getPosition().getX() <= TheSDLSystem::Instance().getScreenWidth())
            {
                (*it)->turnObjOn();
                (*it)->setUpdating(true);
                (*it)->update();
            }
            else
            {
                if ((*it)->objType() != std::string("Player"))
                {
                    (*it)->setUpdating(false);
                    (*it)->scroll(TheGame::Instance().getScrollSpeed());
                }
                else
                {
                    (*it)->update();
                }
            }

            // check if dead or off screen
            if ((*it)->getPosition().getX() < (0 - (*it)->getWidth()) || (*it)->getPosition().getY() > (TheSDLSystem::Instance().getScreenHeight()) || ((*it)->dead()))
            {
                delete* it;
                it = m_gameObjects.erase(it); // erase from vector and get new iterator
            }
            else
            {
                ++it; // increment if all ok
            }

        }
        */
    }
}

void ObjectLayer::render()
{
    for (GameObject* pGameObj : m_gameObjects)
    {
        if (pGameObj->isOn() && pGameObj->isInView())
        {
            pGameObj->draw();
        }
    }
    /*
    for (unsigned int i = 0; i < m_gameObjects.size(); i++)
    {

        if (m_gameObjects[i]->getPosition().getX() <= TheSDLSystem::Instance().getScreenWidth())
        {
            m_gameObjects[i]->draw();
        }
    }
    */
}

