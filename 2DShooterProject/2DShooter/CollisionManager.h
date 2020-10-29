#ifndef __CollisionManager__
#define __CollisionManager__

#include "Singleton.h"
#include "Level.h"
#include <vector>
#include "SDL_Rect.h"

#include "GameObject.h"
#include "TileLayer.h"

struct ObjectCollisionType
{
    std::string name;
    std::vector<SDL_Rect> collisionShape;
    std::map<std::string, std::vector<SDL_Rect>> tileCollisionShape;
    std::vector<std::string> collidesAgainst;
    
    std::vector<std::string> collidesAgainstLayer;
};

class CollisionManager : public Singleton<CollisionManager>
{
public:
    CollisionManager(token) : m_currentLevel(nullptr) {}

    void setCurrentLevel(Level* currentLevel) { m_currentLevel = currentLevel; }

    void addCollisionObject(ObjectCollisionType objColType);
    ObjectCollisionType* getCollisionObject(std::string colType);
 
    bool checkCollision(GameObject* pFocusedObject);

    //maybe
    //std::vector<ObjectCollisionType>& GetCollisionObjects { return m_collisionObjects; }
private:
        Level* m_currentLevel;

        std::vector<ObjectCollisionType> m_collisionObjects;

        void calculateObjColShape(GameObject& focusedObj, ObjectCollisionType& objColType, std::vector<SDL_Rect>& targetShape);
        void calculateTileLayerColShape(TileLayer* pTileLayer, std::vector<SDL_Rect>& targetShape);

        bool testShapeVsShapeCollision(std::vector<SDL_Rect>& collisionShapeA, std::vector<SDL_Rect>& collisionShapeB);
       
};

typedef CollisionManager TheCollisionManager;

#endif /* defined ( __CollisionManager__ ) */