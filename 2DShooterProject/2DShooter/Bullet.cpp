#include "Bullet.h"

Bullet::Bullet() : SDLGameObject()
{
    m_dyingTime = 5;
}

void Bullet::load(std::unique_ptr<LoaderParams> pParams)
{
    SDLGameObject::load(std::move(pParams));
}

void Bullet::draw()
{
    SDLGameObject::draw(); 
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

void Bullet::collision()
{
    m_textureID = "smallexplosion";
    m_currentFrame = 0;
    m_numFrames = 2;
    m_width = 20;
    m_height = 20;
    m_bDying = true;
}

