#include "CollisionManager.h"

#include "Collision.h"
#include "Player.h"
#include "Enemy.h"
#include "BulletHandler.h"
#include "TileLayer.h"

void CollisionManager::checkPlayerEnemyBulletCollision(Player* pPlayer)
{
    SDL_Rect* pRect1 = new SDL_Rect();
    pRect1->x = (int)pPlayer->getPosition().getX();
    pRect1->y = (int)pPlayer->getPosition().getY();
    pRect1->w = (int)pPlayer->getWidth();
    pRect1->h = (int)pPlayer->getHeight();

    for (unsigned int i = 0; i < TheBulletHandler::Instance().getEnemyBullets().size(); i++)
    {
        EnemyBullet* pEnemyBullet = TheBulletHandler::Instance().getEnemyBullets()[i];

        SDL_Rect* pRect2 = new SDL_Rect();
        pRect2->x = (int)pEnemyBullet->getPosition().getX();
        pRect2->y = (int)pEnemyBullet->getPosition().getY();

        pRect2->w = (int)pEnemyBullet->getWidth();
        pRect2->h = (int)pEnemyBullet->getHeight();

        if (RectRect(pRect1, pRect2))
        {
            if (!pPlayer->dying() && !pEnemyBullet->dying())
            {
                pEnemyBullet->collision();
                pPlayer->collision();
            }
        }

        delete pRect2;
    }

    delete pRect1;
}

void CollisionManager::checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*>& objects)
{
    SDL_Rect* pRect1 = new SDL_Rect();
    pRect1->x = (int)pPlayer->getPosition().getX();
    pRect1->y = (int)pPlayer->getPosition().getY();
    pRect1->w = pPlayer->getWidth();
    pRect1->h = pPlayer->getHeight();

    for (unsigned int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->objType() != std::string("Enemy") || !objects[i]->updating())
        {
            continue;
        }

        SDL_Rect* pRect2 = new SDL_Rect();
        pRect2->x = (int)objects[i]->getPosition().getX();
        pRect2->y = (int)objects[i]->getPosition().getY();
        pRect2->w = objects[i]->getWidth();
        pRect2->h = objects[i]->getHeight();

        if (RectRect(pRect1, pRect2))
        {
            if (!objects[i]->dead() && !objects[i]->dying())
            {
                pPlayer->collision();
            }
        }

        delete pRect2;
    }

    delete pRect1;

}

void CollisionManager::checkEnemyPlayerBulletCollision(const std::vector<GameObject*>& objects)
{
    for (unsigned int i = 0; i < objects.size(); i++)
    {
        GameObject* pObject = objects[i];

        for (unsigned int j = 0; j < TheBulletHandler::Instance().getPlayerBullets().size(); j++)
        {
            if (pObject->objType() != std::string("Enemy") || !pObject->updating())
            {
                continue;
            }

            SDL_Rect* pRect1 = new SDL_Rect();
            pRect1->x = (int)pObject->getPosition().getX();
            pRect1->y = (int)pObject->getPosition().getY();
            pRect1->w = (int)pObject->getWidth();
            pRect1->h = (int)pObject->getHeight();

            PlayerBullet* pPlayerBullet = TheBulletHandler::Instance().getPlayerBullets()[j];

            SDL_Rect* pRect2 = new SDL_Rect();
            pRect2->x = (int)pPlayerBullet->getPosition().getX();
            pRect2->y = (int)pPlayerBullet->getPosition().getY();
            pRect2->w = (int)pPlayerBullet->getWidth();
            pRect2->h = (int)pPlayerBullet->getHeight();

            if (RectRect(pRect1, pRect2))
            {
                if (!pObject->dying() && !pPlayerBullet->dying())
                {
                    pPlayerBullet->collision();
                    pObject->collision();
                }

            }

            delete pRect1;
            delete pRect2;
        }
    }

}

void CollisionManager::checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers)
{
    for (std::vector<TileLayer*>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); ++it)
    {
        TileLayer* pTileLayer = (*it);
        std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();

        Vector2D layerPos = pTileLayer->getPosition();

        int x, y, tileColumn, tileRow, tileid = 0;

        x = (int)layerPos.getX() / pTileLayer->getTileSize();
        y = (int)layerPos.getY() / pTileLayer->getTileSize();

        if (pPlayer->getVelocity().getX() >= 0 || pPlayer->getVelocity().getY() >= 0)
        {
            tileColumn = ((int)(pPlayer->getPosition().getX() + pPlayer->getWidth()) / pTileLayer->getTileSize());
            tileRow = ((int)(pPlayer->getPosition().getY() + pPlayer->getHeight()) / pTileLayer->getTileSize());
            tileid = tiles[tileRow + y][tileColumn + x];
        }
        else if (pPlayer->getVelocity().getX() < 0 || pPlayer->getVelocity().getY() < 0)
        {
            tileColumn = (int)pPlayer->getPosition().getX() / pTileLayer->getTileSize();
            tileRow = (int)pPlayer->getPosition().getY() / pTileLayer->getTileSize();
            tileid = tiles[tileRow + y][tileColumn + x];
        }

        if (tileid != 0)
        {
            pPlayer->collision();
        }
    }
}

ObjectCollisionType* CollisionManager::getCollisionObject(std::string colType)
{
    ObjectCollisionType* pObjColType = nullptr;
    for (std::vector<ObjectCollisionType>::iterator itColType = m_collisionObjects.begin();
        itColType != m_collisionObjects.end();
        ++itColType)
    {
        //finds the focused object collision object type
        if (colType == (*itColType).name)
        {
            pObjColType = &(*itColType);
        }
    }

    return pObjColType;
}

void CollisionManager::calculateObjColShape(GameObject& focusedObj, ObjectCollisionType& objColType, std::vector<SDL_Rect>& targetShape)
{
    //adds the object position to object collision box and stores in focusedObjColShape
    for (std::vector<SDL_Rect>::iterator itColBox = objColType.collisionShape.begin();
        itColBox != objColType.collisionShape.end();
        ++itColBox)
    {
        targetShape.push_back(*itColBox);

        targetShape.back().x += focusedObj.getPosition().getX();
        targetShape.back().w += focusedObj.getPosition().getX();

        targetShape.back().y += focusedObj.getPosition().getY();
        targetShape.back().h += focusedObj.getPosition().getY();
    }
}

void CollisionManager::checkCollision(GameObject* pFocusedObject)
{
    ObjectCollisionType* pFocusedObjColType = getCollisionObject(pFocusedObject->objType());

    //tests if the pFocusedObject exists in the vector of ObjectCollisionType
    if (pFocusedObjColType)
    {
        //if focused object doenst have a collide againt list it is passive, skip collision check
        if (!pFocusedObjColType->collidesAgainst.empty())
        {
            //creates a ObjColShapes to test collision against
            std::vector<SDL_Rect> focusedObjColShape;
            std::vector<SDL_Rect> VsObjColShape;

            //adds the object position to object collision box and stores in focusedObjColShape
            calculateObjColShape(*pFocusedObject, *pFocusedObjColType, focusedObjColShape);

            //goes through the collidesAgainst vector to test collision against the VSObjects
            for (std::vector<std::string>::iterator itVSCollision = pFocusedObjColType->collidesAgainst.begin();
                itVSCollision != pFocusedObjColType->collidesAgainst.end();
                ++itVSCollision)
            {
                //loads objects of type to be collided
                std::vector<GameObject*> VsObjects;
                m_currentLevel->getObjectsfromLayers(VsObjects, (*itVSCollision));

                //looks for a collision type for the VSObject
                ObjectCollisionType* pVSObjColType = getCollisionObject(VsObjects.back()->objType());

                //tests if the VsObject exists in the vector of pVSObjColType
                if (pVSObjColType)
                {
                    //goes through the gathered VsObjects to test for collisions
                    for (std::vector<GameObject*>::iterator itVsObject = VsObjects.begin();
                        itVsObject != VsObjects.end();
                        ++itVsObject)
                    {
                        //adds the object position to object collision box and stores in VsObjColShape
                        calculateObjColShape(*(*itVsObject), *pVSObjColType, VsObjColShape);

                        //test collision
                    }
                }               
            }

        }
    }

    //_____________________________-

    SDL_Rect* pRect1 = new SDL_Rect();
    pRect1->x = pFocusedObject->getPosition().getX();
    pRect1->y = pFocusedObject->getPosition().getY();
    pRect1->w = pFocusedObject->getWidth();
    pRect1->h = pFocusedObject->getHeight();

    /*
    for (unsigned int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->objType() != std::string("Enemy") || !objects[i]->updating())
        {
            continue;
        }

        SDL_Rect* pRect2 = new SDL_Rect();
        pRect2->x = (int)objects[i]->getPosition().getX();
        pRect2->y = (int)objects[i]->getPosition().getY();
        pRect2->w = objects[i]->getWidth();
        pRect2->h = objects[i]->getHeight();

        if (RectRect(pRect1, pRect2))
        {
            if (!objects[i]->dead() && !objects[i]->dying())
            {
                pPlayer->collision();
            }
        }

        delete pRect2;
    }

    delete pRect1;
    */
}
