#ifndef __CollisionManager__
#define __CollisionManager__

#include <vector>

class Player;
class GameObject;
class TileLayer;

class CollisionManager
{
public:

    void checkPlayerEnemyBulletCollision(Player* pPlayer);
    void checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*>& objects);
    void checkEnemyPlayerBulletCollision(const std::vector<GameObject*>& objects);
    void checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers);
};

#endif /* defined ( __CollisionManager__ ) */