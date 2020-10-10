#include "BulletHandler.h"

#include "GameObjectFactory.h"
#include "SDLSystem.h"

void BulletHandler::fireBullet(std::string bulletType, Vector2D initialPos, Vector2D heading)
{
    int availableBulletIndex = -1;

    for (int i = 0; i < m_bulletLayer->getGameObjects()->size(); i++)
    {
        if (!m_bulletLayer->getGameObjects()->at(i)->isOn())
        {
            availableBulletIndex = i;
        }
    }

    if (availableBulletIndex < 0)
    {
        addBullet(bulletType);
        availableBulletIndex += m_bulletLayer->getGameObjects()->size();
    }

    m_bulletLayer->getGameObjects()->at(availableBulletIndex)->turnObjOn();
    m_bulletLayer->getGameObjects()->at(availableBulletIndex)->setUpdating(true);
    m_bulletLayer->getGameObjects()->at(availableBulletIndex)->setInView(true);

    m_bulletLayer->getGameObjects()->at(availableBulletIndex)->getPosition() = initialPos;
    m_bulletLayer->getGameObjects()->at(availableBulletIndex)->getVelocity() = heading;

    /*
    //for debugguing
    std::cout << "bullets in pool " << m_bulletLayer->getGameObjects()->size() << "\n";
    std::cout << "using bullet " << availableBulletIndex << "\n";
    */
}

void BulletHandler::addBullet(std::string bulletType)
{
    GameObject* pBullet = TheGameObjectFactory::Instance().create("Bullet");


    //load the bullet with the correct bullet type parameters
    pBullet->load(std::unique_ptr<LoaderParams>(new LoaderParams(m_bulletTypes[bulletType]->getX(), m_bulletTypes[bulletType]->getY(),
        m_bulletTypes[bulletType]->getWidth(), m_bulletTypes[bulletType]->getHeight(),
        m_bulletTypes[bulletType]->getTextureID(), m_bulletTypes[bulletType]->getNumFrames(),
        m_bulletTypes[bulletType]->getLives(), m_bulletTypes[bulletType]->getAnimSpeed(), 
        m_bulletTypes[bulletType]->getSFX())));

    m_bulletLayer->addObjectToLayer(pBullet);
}

void BulletHandler::addPlayerBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading)
{

    PlayerBullet* pPlayerBullet = new PlayerBullet();
   // pPlayerBullet->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames)), heading);
    
}

void BulletHandler::addEnemyBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading)
{
    EnemyBullet* pEnemyBullet = new EnemyBullet();
    //pEnemyBullet->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames)), heading);

    m_enemyBullets.push_back(pEnemyBullet);
}

void BulletHandler::updateBullets()
{
    for (std::vector<PlayerBullet*>::iterator p_it = m_playerBullets.begin(); p_it != m_playerBullets.end();)
    {
        //checks if bullet is out of screen
        if ((*p_it)->getPosition().getX() < 0 || (*p_it)->getPosition().getX() > TheSDLSystem::Instance().getScreenWidth()
            || (*p_it)->getPosition().getY() < 0 || (*p_it)->getPosition().getY() > TheSDLSystem::Instance().getScreenHeight() || (*p_it)->dead())
        {
            //out of screen
                   delete* p_it;
            p_it = m_playerBullets.erase(p_it);
        }
        else
        {
            (*p_it)->update();
            ++p_it;
        }
    }

    for (std::vector<EnemyBullet*>::iterator e_it = m_enemyBullets.begin(); e_it != m_enemyBullets.end();)
    {
        if ((*e_it)->getPosition().getX() < 0 || (*e_it)->getPosition().getX() > TheSDLSystem::Instance().getScreenWidth()
            || (*e_it)->getPosition().getY() < 0 || (*e_it)->getPosition().getY() > TheSDLSystem::Instance().getScreenHeight() || (*e_it)->dead())
        {
            delete* e_it;
            e_it = m_enemyBullets.erase(e_it);
        }
        else
        {
            (*e_it)->update();
            ++e_it;
        }
    }
}

void BulletHandler::drawBullets()
{
    for (unsigned int p = 0; p < m_playerBullets.size(); p++)
    {
        m_playerBullets[p]->draw();
    }

    for (unsigned int e = 0; e < m_enemyBullets.size(); e++)
    {
        m_enemyBullets[e]->draw();
    }
}

void BulletHandler::clearBullets()
{
    m_enemyBullets.clear();
    m_playerBullets.clear();
}
