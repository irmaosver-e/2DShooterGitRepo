#include "ScrollingBackground.h"

#include "SDLSystem.h"
#include "TextureManager.h"

void ScrollingBackground::load(const LoaderParams& rParams)
{
    SDLGameObject::load(rParams);
    m_scrollSpeed = rParams.getAnimSpeed();

    m_srcRect1.x = 0;
    m_destRect1.x = (int)m_position.getX();
    m_srcRect1.y = 0;
    m_destRect1.y = (int)m_position.getY();

    m_srcRect1.w = m_destRect1.w = m_srcRect2Width = m_destRect1Width = m_width;
    m_srcRect1.h = m_destRect1.h = m_height;

    m_srcRect2.x = 0;
    m_destRect2.x = (int)m_position.getX() + m_width;
    m_srcRect2.y = 0;
    m_destRect2.y = (int)m_position.getY();

    m_srcRect2.w = m_destRect2.w = m_srcRect2Width = m_destRect2Width = 0;
    m_srcRect2.h = m_destRect2.h = m_height;
}

void ScrollingBackground::draw()
{
    // draw first rect
    SDL_RenderCopyEx(TheSDLSystem::Instance().getRenderer(), TheTextureManager::Instance().getTextureMap()[m_textureID], &m_srcRect1, &m_destRect1, 0, 0, SDL_FLIP_NONE);

    // draw second rect
    SDL_RenderCopyEx(TheSDLSystem::Instance().getRenderer(), TheTextureManager::Instance().getTextureMap()[m_textureID], &m_srcRect2, &m_destRect2, 0, 0, SDL_FLIP_NONE);

}

void ScrollingBackground::update()
{
    if (m_count == m_maxcount)
    {
        // make first rectangle smaller
        m_srcRect1.x += m_scrollSpeed;
        m_srcRect1.w -= m_scrollSpeed;
        m_destRect1.w -= m_scrollSpeed;

        // make second rectangle bigger
        m_srcRect2.w += m_scrollSpeed;
        m_destRect2.w += m_scrollSpeed;
        m_destRect2.x -= m_scrollSpeed;

        // reset and start again
        if (m_destRect2.w >= m_width)
        {
            m_srcRect1.x = 0;
            m_destRect1.x = (int)m_position.getX();
            m_srcRect1.y = 0;
            m_destRect1.y = (int)m_position.getY();

            m_srcRect1.w = m_destRect1.w = m_srcRect2Width = m_destRect1Width = m_width;
            m_srcRect1.h = m_destRect1.h = m_height;

            m_srcRect2.x = 0;
            m_destRect2.x = (int)m_position.getX() + m_width;
            m_srcRect2.y = 0;
            m_destRect2.y = (int)m_position.getY();

            m_srcRect2.w = m_destRect2.w = m_srcRect2Width = m_destRect2Width = 0;
            m_srcRect2.h = m_destRect2.h = m_height;
        }
        m_count = 0;
    }

    m_count++;
}

void ScrollingBackground::clean()
{
    SDLGameObject::clean();
}