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

    for (int i = 0; i < TheBulletHandler::Instance()->getEnemyBullets().size(); i++)
    {
        EnemyBullet* pEnemyBullet = TheBulletHandler::Instance()->getEnemyBullets()[i];

        SDL_Rect* pRect2 = new SDL_Rect();
        pRect2->x = pEnemyBullet->getPosition().getX();
        pRect2->y = pEnemyBullet->getPosition().getY();

        pRect2->w = pEnemyBullet->getWidth();
        pRect2->h = pEnemyBullet->getHeight();

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
    pRect1->w = (int)pPlayer->getWidth();
    pRect1->h = (int)pPlayer->getHeight();

    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->objType() != std::string("Enemy") || !objects[i]->updating())
        {
            continue;
        }

        SDL_Rect* pRect2 = new SDL_Rect();
        pRect2->x = objects[i]->getPosition().getX();
        pRect2->y = objects[i]->getPosition().getY();
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
    for (int i = 0; i < objects.size(); i++)
    {
        GameObject* pObject = objects[i];

        for (int j = 0; j < TheBulletHandler::Instance()->getPlayerBullets().size(); j++)
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

            PlayerBullet* pPlayerBullet = TheBulletHandler::Instance()->getPlayerBullets()[j];

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
