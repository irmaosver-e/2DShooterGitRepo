#ifndef __Bullet_Handler__
#define __Bullet_Handler__

#include <vector>
#include "Bullet.h"

class BulletHandler
{
public:
    static BulletHandler* Instance();

    void addPlayerBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading);
    void addEnemyBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading);

    void updateBullets();
    void drawBullets();

    void clearBullets();

    const std::vector<PlayerBullet*> getPlayerBullets() { return m_playerBullets; }
    const std::vector<EnemyBullet*> getEnemyBullets() { return m_enemyBullets; }
private:

    BulletHandler() {}
    ~BulletHandler() {}

    BulletHandler(const BulletHandler&);
    BulletHandler& operator=(const BulletHandler&) {}

    static BulletHandler* s_pInstance;

    // in play bullets
    std::vector<PlayerBullet*> m_playerBullets;
    std::vector<EnemyBullet*> m_enemyBullets;
};

typedef BulletHandler TheBulletHandler;

#endif /* defined ( __Bullet_Handler__ ) */
