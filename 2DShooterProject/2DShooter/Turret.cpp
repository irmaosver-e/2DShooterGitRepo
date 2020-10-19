#include "Turret.h"

#include "Game.h"
#include "SoundManager.h"
#include "BulletHandler.h"

Turret::Turret()
{
    m_dyingTime = 1000;
    m_health = 15;
    m_bulletFiringSpeed = 50;
}

void Turret::collision()
{
    m_health -= 1;

    if (m_health == 0)
    {
        if (!m_bPlayedDeathSound)
        {
            TheSoundManager::Instance().playSound("explode", 0);

            m_textureID = "largeexplosion";
            m_currentFrame = 0;
            m_numFrames = 9;
            m_width = 60;
            m_height = 60;
            m_bDying = true;
        }
    }
}

void Turret::update()
{
    if (!m_bDying)
    {
        // we want to scroll this object with the rest
       // scroll(TheGame::Instance().getScrollSpeed());

        if (m_bulletCounter == m_bulletFiringSpeed)
        {
          // TheBulletHandler::Instance().addEnemyBullet((int)m_position.getX(), (int)m_position.getY(), 16, 16, "bullet2", 1, Vector2D(-3, -3));
          // TheBulletHandler::Instance().addEnemyBullet((int)m_position.getX() + 20, (int)m_position.getY(), 16, 16, "bullet2", 1, Vector2D(0, -3));
           //TheBulletHandler::Instance().addEnemyBullet((int)m_position.getX() + 40, (int)m_position.getY(), 16, 16, "bullet2", 1, Vector2D(3, -3));
            m_bulletCounter = 0;
        }

        m_bulletCounter++;
    }
    else
    {
        //scroll(TheGame::Instance().getScrollSpeed());
        doDyingAnimation();
    }
}
