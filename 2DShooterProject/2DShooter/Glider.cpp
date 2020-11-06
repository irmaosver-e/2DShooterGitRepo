#include "Glider.h"
#include "SoundManager.h"

Glider::Glider() : Enemy()
{
    m_dyingTime = 25;
    m_health = 1;
    m_moveSpeed = 3;
    m_gap = 60;
}

void Glider::load(const LoaderParams& rParams)
{
    SDLGameObject::load(rParams);

    m_velocity.getXRef() = (float)-m_moveSpeed;
    m_velocity.getYRef() = (float)m_moveSpeed / 2;

    m_maxHeight = (int)m_position.getY() + m_gap;
    m_minHeight = (int)m_position.getY() - m_gap;
}

void Glider::update()
{
    if (!m_bDying)
    {
        if (m_position.getY() >= m_maxHeight)
        {
            m_velocity.getYRef() = (float)-m_moveSpeed;
        }
        else if (m_position.getY() <= m_minHeight)
        {
            m_velocity.getYRef() = m_moveSpeed;
        }
    }
    else
    {
        m_velocity.getXRef() = 0;
        m_velocity.getYRef() = 0;
        handleDying();
    }

    SDLGameObject::update();
}

void Glider::collision()
{
    m_health -= 1;

    if (m_health == 0)
    {
        if (!m_bPlayedDeathSound)
        {
            TheSoundManager::Instance().playSound("explode", 0);

            m_textureID = "explosion";
            m_currentFrame = 0;
            m_numFrames = 9;
            m_width = 40;
            m_height = 40;
            m_bDying = true;
        }
    }

}
