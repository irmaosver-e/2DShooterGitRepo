#ifndef __Bullet_Handler__
#define __Bullet_Handler__

#include <vector>
#include "Singleton.h"
#include "Bullet.h"

class BulletHandler : public Singleton<BulletHandler>
{
public:
    BulletHandler(token) {}
    ~BulletHandler() {}

    void addPlayerBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading);
    void addEnemyBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading);

    void updateBullets();
    void drawBullets();

    void clearBullets();

    const std::vector<PlayerBullet*> getPlayerBullets() { return m_playerBullets; }
    const std::vector<EnemyBullet*> getEnemyBullets() { return m_enemyBullets; }
private:
    // in play bullets
    std::vector<PlayerBullet*> m_playerBullets;
    std::vector<EnemyBullet*> m_enemyBullets;
};

typedef BulletHandler TheBulletHandler;

#endif /* defined ( __Bullet_Handler__ ) */
