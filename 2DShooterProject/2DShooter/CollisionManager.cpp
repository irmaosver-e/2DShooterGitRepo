#include "CollisionManager.h"

#include "Player.h"
#include "Enemy.h"
#include "BulletHandler.h"

#include "SDLSystem.h"

ObjectCollisionType* CollisionManager::getCollisionObject(std::string colType)
{
    ObjectCollisionType* pObjColType = nullptr;
    
    for(unsigned int i = 0; i < m_collisionObjects.size(); i++)
    {
        //finds the focused object collision object type
        if (colType == m_collisionObjects[i].name)
        {
            pObjColType = &m_collisionObjects[i];
        }
    }

    return pObjColType;
}

void CollisionManager::calculateObjColShape(GameObject& focusedObj, ObjectCollisionType& objColType, std::vector<SDL_Rect>& targetShape)
{
    //adds the object position to object collision box and stores in focusedObjColShape
    for (SDL_Rect colBox : objColType.collisionShape)
    {
        targetShape.push_back(colBox);

        targetShape.back().x += focusedObj.getPosition().getX();
        targetShape.back().y += focusedObj.getPosition().getY();

        // draws collision boxes and texture boxes for debugging
        //include SDL_Systems
        /*
        SDL_Rect objTexture;
        objTexture.x = focusedObj.getPosition().getX();
        objTexture.y = focusedObj.getPosition().getY();
        objTexture.w = focusedObj.getWidth();
        objTexture.h = focusedObj.getHeight();

        SDL_SetRenderDrawColor(TheSDLSystem::Instance().getRenderer(), 255,0,0,0);
        SDL_RenderDrawRect(TheSDLSystem::Instance().getRenderer(), &objTexture);
        SDL_RenderPresent(TheSDLSystem::Instance().getRenderer());

        SDL_SetRenderDrawColor(TheSDLSystem::Instance().getRenderer(), 0, 255, 0, 0);
        SDL_RenderDrawRect(TheSDLSystem::Instance().getRenderer(), &targetShape.back());
        SDL_RenderPresent(TheSDLSystem::Instance().getRenderer());  

        */
    }
}


void CollisionManager::calculateTileLayerColShape(TileLayer* pTileLayer, std::vector<SDL_Rect>& targetShape)
{
    Vector2Df layerPos = pTileLayer->getPosition();

    //calculate the layer Shape
    int firstOnScreenColumn = layerPos.getX() / pTileLayer->getTileWidth();
    int firstOnScreenRow = layerPos.getY() / pTileLayer->getTileHeight();

    int onScreenColumns = TheSDLSystem::Instance().getScreenWidth() / pTileLayer->getTileWidth();
    int onScreenRows = TheSDLSystem::Instance().getScreenHeight() / pTileLayer->getTileHeight();

    for (int row = 0; row < onScreenRows; row++)
    {
        for (int col = 0; col < onScreenColumns; col++)
        {
            if (pTileLayer->getTileIDs()[row + firstOnScreenRow][col + firstOnScreenColumn] != 0)
            {
                SDL_Rect colBox;
                colBox.x = 0;
                colBox.y = 0;
                colBox.w = pTileLayer->getTileWidth();
                colBox.h = pTileLayer->getTileHeight();
                targetShape.push_back(colBox);

                int tileXoffset = (int)layerPos.getX() % pTileLayer->getTileWidth();
                int tileYoffset = (int)layerPos.getY() % pTileLayer->getTileHeight();

                targetShape.back().x += (col * pTileLayer->getTileWidth()) - tileXoffset;
                targetShape.back().y = (row * pTileLayer->getTileHeight()) - tileYoffset;
            }
        }
    }
}

bool CollisionManager::testShapeVsShapeCollision(std::vector<SDL_Rect>& collisionShapeA, std::vector<SDL_Rect>& collisionShapeB)
{
    for(unsigned int i = 0; i < collisionShapeA.size(); i++)
    {
        for (unsigned int j = 0; j < collisionShapeB.size(); j++)
        {         
            if (SDL_HasIntersection(&collisionShapeA[i], &collisionShapeB[j]))
            {
                return true;
            }
        }
    }
    return false;
}

bool CollisionManager::checkCollision(GameObject* pFocusedObject)
{
    ObjectCollisionType* pFocusedObjColType = getCollisionObject(pFocusedObject->getTextureID());

    //tests if the pFocusedObject exists in the vector of ObjectCollisionType
    if (pFocusedObjColType)
    {
        //adds the object position to object collision box and stores in focusedObjColShape
        std::vector<SDL_Rect> focusedObjColShape;
        calculateObjColShape(*pFocusedObject, *pFocusedObjColType, focusedObjColShape);

        //if focused object doenst have a collide againt list it is passive, skip collision check
        if (!pFocusedObjColType->collidesAgainst.empty())
        {
            //goes through the collidesAgainst vector to test collision against the VSObjects
            for(std::string versusCollision : pFocusedObjColType->collidesAgainst)
            {
                //loads objects of type to be collided
                std::vector<GameObject*> VsObjects;
                m_currentLevel->getObjectsfromLayers(VsObjects, versusCollision);

                //looks for a collision type for the VSObject
                ObjectCollisionType* pVSObjColType = getCollisionObject(versusCollision);
                                
                //tests if the VsObject exists in the vector of pVSObjColType
                if (pVSObjColType)
                {
                    //goes through the gathered VsObjects to test for collisions
                    for (GameObject* pVSObject : VsObjects)
                    {
                        //test collision only if the VSObject is active
                        if (pVSObject->isOn())
                        {
                            //adds the object position to object collision box and stores in VsObjColShape
                            std::vector<SDL_Rect> VsObjColShape;
                            calculateObjColShape(*pVSObject, *pVSObjColType, VsObjColShape);

                            //test collision shapes
                            if (testShapeVsShapeCollision(focusedObjColShape, VsObjColShape))
                            {
                                pFocusedObject->collision();
                                pFocusedObject->isColliding() = true;
                                pVSObject->isColliding() = true;


                                pVSObject->collisionPassive();

                                return true;
                            }
                        }

                        pFocusedObject->isColliding() = false;
                        pVSObject->isColliding() = false;
                    }
                }               
            }
        }

        //if focused object doenst have a collide against Layer list it is passive against Layers, skip collision check
        if (!pFocusedObjColType->collidesAgainstLayer.empty())
        {
            //goes through the collidesAgainstLayer vector to test collision against the LayerTiles
            for (std::string tileLayerCollision : pFocusedObjColType->collidesAgainstLayer)
            {
               //adds the layer position to tiles collision box and stores in layerShape
               std::vector<SDL_Rect> layerShape;
               calculateTileLayerColShape(m_currentLevel->getTileLayerByName(tileLayerCollision), layerShape);
                
                /*
                * 
                * could use part of this code to improve speed of code
                if (pFocusedObject->getVelocity().getX() >= 0 || pFocusedObject->getVelocity().getY() >= 0)
                {
                    tileColumn = ((int)(pFocusedObject->getPosition().getX() + pFocusedObject->getWidth()) / pVSTileLayer->getTileWidth());
                    tileRow = ((int)(pFocusedObject->getPosition().getY() + pFocusedObject->getHeight()) / pVSTileLayer->getTileHeight());
                    tileid = pVSTileLayer->getTileIDs()[tileRow + y][tileColumn + x];
                }
                else if (pFocusedObject->getVelocity().getX() < 0 || pFocusedObject->getVelocity().getY() < 0)
                {
                    tileColumn = (int)pFocusedObject->getPosition().getX() / pVSTileLayer->getTileWidth();
                    tileRow = (int)pFocusedObject->getPosition().getY() / pVSTileLayer->getTileHeight();
                    tileid = pVSTileLayer->getTileIDs()[tileRow + y][tileColumn + x];
                }

                if (tileid != 0)
                {
                    pFocusedObject->collision();
                    pFocusedObject->isColliding() = true;
                    return true;
                }
                */


                //test collision shapes
                if (testShapeVsShapeCollision(focusedObjColShape, layerShape))
                {
                    pFocusedObject->collisionWithLayer();
                    pFocusedObject->isColliding() = true;

                    return true;
                }
                pFocusedObject->isColliding() = false;

            }
        }
    }
    return false;
}
