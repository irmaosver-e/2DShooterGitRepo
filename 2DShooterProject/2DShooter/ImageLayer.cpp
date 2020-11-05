#include "ImageLayer.h"
#include "SDLSystem.h"

ImageLayer::~ImageLayer()
{
    for (GameObject* pGameObj : m_gameObjects)
    {
        delete pGameObj;
    }
    m_gameObjects.clear();
}

//needs revision
void ImageLayer::update()
{
    //checks if the layers is not tiled only 1 object
    if (m_gameObjects.size() == 1)
    {
        m_gameObjects.back()->update();

        if (m_gameObjects.back()->isOn())
        {
            m_gameObjects.back()->scroll(m_scrollSpeed);
            m_gameObjects.back()->inViewCheck();

            //needs to be out of view to the left
            if (!m_gameObjects.back()->isInView() && m_gameObjects.back()->getPosition().getX() < 0)
            {
                m_gameObjects.back()->turnObjOff();
            }
        }
    }
    else
    {
        for (GameObject* pGameObj : m_gameObjects)
        {
            pGameObj->update();

            if (pGameObj->isOn())
            {
                pGameObj->scroll(m_scrollSpeed);
                pGameObj->inViewCheck();

                //needs to be out of view to the left
                if (!pGameObj->isInView() && pGameObj->getPosition().getX() < 0)
                {
                    //calculates the position to be after the last object
                    pGameObj->getPosition().getXRef() = pGameObj->getWidth() * (m_gameObjects.size() - 1);
                }
            }
        }
    }
}

void ImageLayer::render()
{
    for (GameObject* pGameObj : m_gameObjects)
    {
        if (pGameObj->isOn() && pGameObj->isInView())
        {
            pGameObj->draw();
        }
    }
}

void ImageLayer::resetPosition()
{
    if (m_gameObjects.size() == 1)
    {
        m_gameObjects.back()->turnObjOn();
        m_gameObjects.back()->getPosition().getXRef() = m_initialPos.getX();
        m_gameObjects.back()->getPosition().getYRef() = m_initialPos.getY();
    }
    else
    {
        if (!m_gameObjects.empty())
        {
            for (int i = 0; i < m_gameObjects.size(); i++)
            {
                m_gameObjects[i]->getPosition().getXRef() = m_gameObjects[i]->getWidth() * i;
            }
        }
    }
}
