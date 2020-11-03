#include "Bullet.h"

Bullet::Bullet() : SDLGameObject()
{
    m_dyingTime = 5;
}


void Bullet::update()
{
    if (!m_bDying && m_bUpdating)
    {
        SDLGameObject::update();
    }
    else
    {
        //doDyingAnimation();
    }
}

void Bullet::outOfView()
{ 
    turnObjOff();
}

void Bullet::collision()
{
    m_textureID = "smallexplosion";
    m_currentFrame = 0;
    m_numFrames = 2;
    m_width = 20;
    m_height = 20;
    m_bDying = true;
}

void Bullet::collisionPassive()
{
    outOfView();
}

void Bullet::collisionWithLayer()
{
    outOfView();
}

