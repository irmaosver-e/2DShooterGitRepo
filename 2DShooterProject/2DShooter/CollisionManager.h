#ifndef __CollisionManager__
#define __CollisionManager__

#include "Singleton.h"
#include <vector>

struct ObjectCollisionType
{
    std::string name;
    std::vector<SDL_Rect> collisionShape;
    std::vector<std::string> collidesAgainst;
    
    //possible implementation
    //std::vector<std::string> collidesAgainstLayer;
};

class Player;
class GameObject;
class TileLayer;

class CollisionManager : public Singleton<CollisionManager>
{
public:
    CollisionManager(token) {}

    //to be made redundant
    void checkPlayerEnemyBulletCollision(Player* pPlayer);
    void checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*>& objects);
    void checkEnemyPlayerBulletCollision(const std::vector<GameObject*>& objects);
    void checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers);

    std::vector<ObjectCollisionType>& GetCollisionObjects { return m_collisionObjects; }

private:
        std::vector<ObjectCollisionType> m_collisionObjects;
};

typedef CollisionManager TheCollisionManager;

#endif /* defined ( __CollisionManager__ ) */