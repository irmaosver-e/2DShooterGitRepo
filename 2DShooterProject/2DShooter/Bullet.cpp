#include "Bullet.h"

Bullet::Bullet() : SDLGameObject()
{
}


void Bullet::reset(const LoaderParams& rParams, Vector2Df* position)
{
    outOfView();
    
    if (position)
    {
        m_position = *position;
    }
}

void Bullet::update()
{
    SDLGameObject::update();
}

void Bullet::outOfView()
{ 
    turnObjOff();
}

void Bullet::collision()
{
   // m_textureID = "smallexplosion";
   // m_currentFrame = 0;
   // m_numFrames = 2;
   // m_width = 20;
   // m_height = 20;
    //m_bDying = true;
}

void Bullet::collisionPassive()
{
    outOfView();
}

void Bullet::collisionWithLayer()
{
    outOfView();
}

