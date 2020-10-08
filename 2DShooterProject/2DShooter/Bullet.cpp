#include "Bullet.h"

Bullet::Bullet() : SDLGameObject()
{
    m_dyingTime = 5;
}

void Bullet::load(std::unique_ptr<LoaderParams> pParams, Vector2D heading)
{
    SDLGameObject::load(std::move(pParams));
    m_heading = heading;
}

void Bullet::update()
{
    if (!m_bDying)
    {
        m_velocity.setX(m_heading.getX());
        m_velocity.setY(m_heading.getY());

        SDLGameObject::update();
    }
    else
    {
        m_velocity.setX(0);
        m_velocity.setY(0);
        doDyingAnimation();
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

