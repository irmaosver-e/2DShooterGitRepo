#include "BulletHandler.h"

#include "GameObjectFactory.h"
#include "SDLSystem.h"

void BulletHandler::registerBulletType(std::string bulletType, LoaderParams& params)
{
    //checks if the bulletType already exist before creating
    std::map<std::string, LoaderParams>::iterator it = m_bulletTypes.find(bulletType);
    if (it == m_bulletTypes.end())
    {
        m_bulletTypes[bulletType] = params;
    }
}

void BulletHandler::registerFiringPoint(std::string firingObj, FiringPoint& firingPoint)
{
    //checks if the firingObj already exist before creating
    std::map<std::string, FiringPoint>::iterator it = m_objFire.find(firingObj);
    if (it == m_objFire.end())
    {
        m_objFire[firingObj] = firingPoint;
    }
}

LoaderParams* BulletHandler::getBulletTypeParam(std::string bulletType)
{
    //checks if the firingObj already exist before creating
    std::map<std::string, LoaderParams>::iterator it = m_bulletTypes.find(bulletType);
    if (it != m_bulletTypes.end())
    {
       return &m_bulletTypes[bulletType];
    }
    
    return nullptr;
}

void BulletHandler::fireBullet(std::string firingObj, Vector2Df firingObjPos, Vector2Df heading)
{
    int availableBulletIndex = -1;

    for (unsigned int i = 0; i < m_bulletLayer->getGameObjects()->size(); i++)
    {
        //checks if bullet is available
        if (!m_bulletLayer->getGameObjects()->at(i)->isOn())
        {
            //test if the bullet available is of same bullet type fired
            if (m_bulletLayer->getGameObjects()->at(i)->objType() == m_objFire[firingObj].bulletType)
            {
                availableBulletIndex = i;
            }
        }
    }

    if (availableBulletIndex < 0)
    {
        addBullet(m_objFire[firingObj].bulletType);
        availableBulletIndex += m_bulletLayer->getGameObjects()->size();

        //for debugging
        //std::cout << "bullet added: " << bulletType <<"/ pool size " << availableBulletIndex << "\n";
    }

    m_bulletLayer->getGameObjects()->at(availableBulletIndex)->turnObjOn();
    m_bulletLayer->getGameObjects()->at(availableBulletIndex)->setUpdating(true);
    m_bulletLayer->getGameObjects()->at(availableBulletIndex)->setInView(true);

    Vector2Df firingPointCoord(m_objFire[firingObj].position.getX() , m_objFire[firingObj].position.getY());
    Vector2Df bulletAnchorPoint = *m_bulletTypes[m_objFire[firingObj].bulletType].getAnchorPointPtr();
    m_bulletLayer->getGameObjects()->at(availableBulletIndex)->getPosition() = firingObjPos + (firingPointCoord - bulletAnchorPoint);
    m_bulletLayer->getGameObjects()->at(availableBulletIndex)->getVelocity() = heading;

    
    //for debugguing
    //std::cout << "bullets in pool: " << m_bulletLayer->getGameObjects()->size() << " / using bullet: " << availableBulletIndex << " / type asked: " << bulletType << " / type used: " << m_bulletLayer->getGameObjects()->at(availableBulletIndex)->getTextureID() << "\n";
       
}

void BulletHandler::addBullet(std::string bulletType)
{
    GameObject* pBullet = TheGameObjectFactory::Instance().create(bulletType);

    pBullet->load(m_bulletTypes[bulletType]);

    m_bulletLayer->addObjectToLayer(pBullet);
}
