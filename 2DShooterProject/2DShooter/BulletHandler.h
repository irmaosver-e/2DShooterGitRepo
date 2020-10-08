#ifndef __Bullet_Handler__
#define __Bullet_Handler__

#include <vector>
#include <map>
#include "Singleton.h"
#include "Bullet.h"
#include "ObjectLayer.h"

class BulletHandler : public Singleton<BulletHandler>
{
public:
    BulletHandler(token) {}
    ~BulletHandler() {}

    void registerBulletLayer(ObjectLayer* pBulletLayer) { m_bulletLayer = pBulletLayer; }
    void registerBulletType(std::string bulletType, LoaderParams* pParams) { m_bulletTypes[bulletType] = pParams; }

    void fireBullet(std::string bulletType, Vector2D heading);

    void addPlayerBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading);
    void addEnemyBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading);

    void updateBullets();
    void drawBullets();

    void clearBullets();

    const std::vector<PlayerBullet*> getPlayerBullets() { return m_playerBullets; }
    const std::vector<EnemyBullet*> getEnemyBullets() { return m_enemyBullets; }

private:
    void addBullet(std::string bulletType);
    
    ObjectLayer* m_bulletLayer;

    std::map<std::string, LoaderParams*> m_bulletTypes;

    // in play bullets
    //std::vector<GameObject*> m_bullets;
    std::vector<PlayerBullet*> m_playerBullets;
    std::vector<EnemyBullet*> m_enemyBullets;
};

typedef BulletHandler TheBulletHandler;

#endif /* defined ( __Bullet_Handler__ ) */
