#include "BulletHandler.h"

#include "GameObjectFactory.h"
#include "SDLSystem.h"

void BulletHandler::fireBullet(std::string firingObj, Vector2D firingObjPos, Vector2D heading)
{
    int availableBulletIndex = -1;

    for (int i = 0; i < m_bulletLayer->getGameObjects()->size(); i++)
    {
        //checks if bullet is available
        if (!m_bulletLayer->getGameObjects()->at(i)->isOn())
        {
            //test if the bullet available is of same bullet type fired
            if (m_bulletLayer->getGameObjects()->at(i)->getTextureID() == m_bulletTypes[m_firingPoints[firingObj].bulletType].getTextureID())
            {
                availableBulletIndex = i;
            }
        }
    }

    if (availableBulletIndex < 0)
    {
        addBullet(m_firingPoints[firingObj].bulletType);
        availableBulletIndex += m_bulletLayer->getGameObjects()->size();

        //for debugging
        //std::cout << "bullet added: " << bulletType <<"/ pool size " << availableBulletIndex << "\n";
    }

    m_bulletLayer->getGameObjects()->at(availableBulletIndex)->turnObjOn();
    m_bulletLayer->getGameObjects()->at(availableBulletIndex)->setUpdating(true);
    m_bulletLayer->getGameObjects()->at(availableBulletIndex)->setInView(true);

    Vector2D firingPointCoord(m_firingPoints[firingObj].x, m_firingPoints[firingObj].y);
    m_bulletLayer->getGameObjects()->at(availableBulletIndex)->getPosition() = firingObjPos + firingPointCoord;
    m_bulletLayer->getGameObjects()->at(availableBulletIndex)->getVelocity() = heading;

    
    //for debugguing
    //std::cout << "bullets in pool: " << m_bulletLayer->getGameObjects()->size() << " / using bullet: " << availableBulletIndex << " / type asked: " << bulletType << " / type used: " << m_bulletLayer->getGameObjects()->at(availableBulletIndex)->getTextureID() << "\n";
       
}

void BulletHandler::addBullet(std::string bulletType)
{
    GameObject* pBullet = TheGameObjectFactory::Instance().create("Bullet");


    //load the bullet with the correct bullet type parameters
    pBullet->load(std::unique_ptr<LoaderParams>(new LoaderParams(m_bulletTypes[bulletType].getX(), m_bulletTypes[bulletType].getY(),
        m_bulletTypes[bulletType].getWidth(), m_bulletTypes[bulletType].getHeight(),
        m_bulletTypes[bulletType].getTextureID(), m_bulletTypes[bulletType].getNumFrames(),
        m_bulletTypes[bulletType].getLives(), m_bulletTypes[bulletType].getAnimSpeed(), 
        m_bulletTypes[bulletType].getSFX())));

    m_bulletLayer->addObjectToLayer(pBullet);
}
