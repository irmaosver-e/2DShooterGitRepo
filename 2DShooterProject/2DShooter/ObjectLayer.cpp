#include "ObjectLayer.h"

#include "Game.h"
#include "SDLSystem.h"
#include "CollisionManager.h"
#include "ObjectSpawner.h"
#include "GameObject.h"
#include "Level.h"


ObjectLayer::~ObjectLayer()
{
    for (GameObject* pGameObj : m_gameObjects)
    {
        delete pGameObj;
    }
    m_gameObjects.clear();
}

void ObjectLayer::update()
{
     for (ObjectMarker& objMarker : m_objectMarkers)
    {
        //scroll marker
        objMarker.objPositionMarker.getXRef() -= m_scrollSpeed;
        
        TheObjectSpawner::Instance().spawnObject(*this, objMarker);

    }
    
     // iterate through the objects
     for (GameObject* pGameObj : m_gameObjects)
    {
        pGameObj->update();

        if (pGameObj->isOn())
        {
            pGameObj->scroll(m_scrollSpeed);
            pGameObj->inViewCheck();

            if (pGameObj->isInView())
            {
                pGameObj->inView();
                TheCollisionManager::Instance().checkCollision(pGameObj);
            }
            else
            {
                pGameObj->outOfView();
            }
        }
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
}

void ObjectLayer::reset()
{
    resetMarkers(); 
    turnObjectsOff();
}

void ObjectLayer::resetMarkers()
{
    for (ObjectMarker& rMarker : m_objectMarkers)
    {
        rMarker.reset();
    }
}

void ObjectLayer::turnObjectsOff()
{
    for (GameObject* pGameObj : m_gameObjects)
    {
        pGameObj->turnObjOff();
    }
}

