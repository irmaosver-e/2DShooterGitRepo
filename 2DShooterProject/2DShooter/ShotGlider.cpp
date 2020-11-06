#include "ShotGlider.h"

#include "BulletHandler.h"

ShotGlider::ShotGlider() : Glider()
{
    m_bulletFiringSpeed = 25;
    m_moveSpeed = 3;
}

void ShotGlider::load(const LoaderParams& rParams)
{
    SDLGameObject::load(rParams);

	m_velocity.getXRef() = (float)-m_moveSpeed;
}

void ShotGlider::update()
{
    if (!m_bDying)
    {
        if (m_bulletCounter == m_bulletFiringSpeed)
        {
            //TheBulletHandler::Instance().addEnemyBullet((int)m_position.getX(), (int)m_position.getY() + 15, 16, 16, "bullet2", 1, Vector2D(-10, 0));
            m_bulletCounter = 0;
        }

        m_bulletCounter++;
    }
    else
    {
        m_velocity.getXRef() = 0;
        handleDying();
    }

    SDLGameObject::update();
}
