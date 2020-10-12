#include "Eskeletor.h"
#include "SoundManager.h"
#include "BulletHandler.h"
#include "Game.h"

Eskeletor::Eskeletor() : Enemy()
{
    m_dyingTime = 50;
    m_health = 2;
    m_moveSpeed = 1;
    m_bulletFiringSpeed = 50;
}

void Eskeletor::collision()
{
    m_health -= 1;

    if (m_health == 0)
    {
        if (!m_bPlayedDeathSound)
        {
            //TheSoundManager::Instance().playSound("explode", 0);

           // m_textureID = "largeexplosion";
            m_currentFrame = 0;
            m_numFrames = 2;
            m_width = 60;
            m_height = 60;
            m_bDying = true;
        }

    }
}

void Eskeletor::update()
{
    if (!m_bDying)
    {
        scroll((float)(TheGame::Instance().getScrollSpeed()));
        
        m_velocity.setY((float)m_moveSpeed);

        if (m_bulletCounter == m_bulletFiringSpeed)
        {
           // TheBulletHandler::Instance().addEnemyBullet((int)m_position.getX(), (int)m_position.getY(), 16, 16, "bullet1", 1, Vector2D(-3, 0));
           // TheBulletHandler::Instance().addEnemyBullet((int)m_position.getX(), (int)m_position.getY(), 16, 16, "bullet1", 1, Vector2D(3, 0));
           TheBulletHandler::Instance().fireBullet(m_defaultBullet, m_position, Vector2D(-10, 0));

            m_bulletCounter = 0;
        }
        m_bulletCounter++;

    }
    else
    {
        m_velocity.setY(0);
        doDyingAnimation();
    }

    SDLGameObject::update();
}
