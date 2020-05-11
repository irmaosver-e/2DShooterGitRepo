#ifndef __CollisionManager__
#define __CollisionManager__

#include <vector>

#include "BulletHandler.h"
#include "Collision.h"
#include "TileLayer.h"
#include "Player.h"
#include "Enemy.h"


class GameObject;

class CollisionManager
{
public:

    void checkPlayerEnemyBulletCollision(Player* pPlayer);
    void checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*>& objects);
    void checkEnemyPlayerBulletCollision(const std::vector<GameObject*>& objects);
    void checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers);
};

#endif /* defined ( __CollisionManager__ ) */