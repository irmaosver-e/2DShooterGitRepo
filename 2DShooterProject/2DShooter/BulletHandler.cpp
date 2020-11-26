#include "BulletHandler.h"

#include "GameObjectFactory.h"
#include "SDLSystem.h"

void BulletHandler::registerBulletType(std::string bulletType, LoaderParams& params)
{
    //checks if the bulletType already exist before creating
    if (m_bulletTypes.find(bulletType) == m_bulletTypes.end())
    {
        m_bulletTypes[bulletType] = params;
    }
}

void BulletHandler::registerFiringPoint(std::string firingObj, std::string ownerTile, std::vector<FiringPoint>& firingPoints)
{

    //checks if the firingObj or ownerTile is new
    if (m_objFirePoints.find(firingObj) == m_objFirePoints.end() || m_objFirePoints[firingObj].find(ownerTile) == m_objFirePoints[firingObj].end())
    {
        m_objFirePoints[firingObj][ownerTile] = firingPoints;
    }
}

LoaderParams* BulletHandler::getBulletTypeParam(std::string bulletType)
{
    //checks if the firingObj exist before creating in order to return
    if (m_bulletTypes.find(bulletType) != m_bulletTypes.end())
    {
       return &m_bulletTypes[bulletType];
    }
    
    return nullptr;
}

void BulletHandler::fireBullet(std::string& firingObj, std::string& currentAnimation, Vector2Df firingObjPos, Vector2Df heading, std::string bulletType)
{
    std::vector<FiringPoint*> firingPoints;
    
    //fire from all firing points
    if (bulletType != "all")
    {
        for (FiringPoint& firingPoint : m_objFirePoints[firingObj][currentAnimation])
        {
            if (firingPoint.bulletType == bulletType)
            {
                firingPoints.push_back(&firingPoint);
            }
        }
    }
    else
    {
         for (FiringPoint& firingPoint : m_objFirePoints[firingObj][currentAnimation])
        {
            firingPoints.push_back(&firingPoint);
        }
    }
    
    for (FiringPoint* pFiringPoint : firingPoints)
    {
        int availableBulletIndex = -1;

        for (unsigned int i = 0; i < m_bulletLayer->getGameObjects()->size(); i++)
        {
            //checks if bullet is available
            if (!m_bulletLayer->getGameObjects()->at(i)->isOn())
            {
                //test if the bullet available is of same bullet type fired
                if (m_bulletLayer->getGameObjects()->at(i)->objType() == pFiringPoint->bulletType)
                {
                    availableBulletIndex = i;
                }
            }
        }

        if (availableBulletIndex < 0)
        {
            addBullet(pFiringPoint->bulletType);
            availableBulletIndex += m_bulletLayer->getGameObjects()->size();

            //for debugging
            //std::cout << "bullet added: " << bulletType <<"/ pool size " << availableBulletIndex << "\n";
        }


            m_bulletLayer->getGameObjects()->at(availableBulletIndex)->turnObjOn();
            m_bulletLayer->getGameObjects()->at(availableBulletIndex)->setUpdating(true);
            m_bulletLayer->getGameObjects()->at(availableBulletIndex)->setInView(true);

            Vector2Df firingPointCoord(pFiringPoint->position.getX(), pFiringPoint->position.getY());
            Vector2Df bulletAnchorPoint = *m_bulletTypes[pFiringPoint->bulletType].getAnchorPointPtr();
            m_bulletLayer->getGameObjects()->at(availableBulletIndex)->getPosition() = firingObjPos + (firingPointCoord - bulletAnchorPoint);
            m_bulletLayer->getGameObjects()->at(availableBulletIndex)->getVelocity() = heading;
    }
    
    //for debugguing
    //std::cout << "bullets in pool: " << m_bulletLayer->getGameObjects()->size() << " / using bullet: " << availableBulletIndex << " / type asked: " << bulletType << " / type used: " << m_bulletLayer->getGameObjects()->at(availableBulletIndex)->getTextureID() << "\n";
       
}

void BulletHandler::addBullet(std::string bulletType)
{
    GameObject* pBullet = TheGameObjectFactory::Instance().create(bulletType);

    pBullet->load(m_bulletTypes[bulletType]);

    m_bulletLayer->addObjectToLayer(pBullet);
}
